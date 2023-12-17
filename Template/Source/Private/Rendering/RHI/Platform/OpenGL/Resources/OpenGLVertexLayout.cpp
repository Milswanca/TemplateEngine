#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLVertexLayout.h"
#include <glad\glad.h>

std::unordered_map<VertexAttributeTypes, GLenum> OpenGLVertexLayout::s_VertexAttribTypeToOGL = {
	{ VertexAttributeTypes::Float, GL_FLOAT },
	{ VertexAttributeTypes::Int, GL_INT },
};

OpenGLVertexLayout::OpenGLVertexLayout(const RHIVertexAttributeArray& InAttribs) : RHIVertexLayout(InAttribs)
{
	glGenVertexArrays(1, &m_LayoutID);
	glBindBuffer(GL_ARRAY_BUFFER, m_LayoutID);

	int NumAttributes = GetNumAttributes();
	for (int i = 0; i < NumAttributes; ++i)
	{
		const RHIVertexAttributeDesc Attrib = GetAttribute(i);
		GLenum AttribType = s_VertexAttribTypeToOGL[Attrib.m_Type];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, Attrib.m_NumChannels, AttribType, Attrib.m_bNormalize, Attrib.m_Stride, &Attrib.m_Offset);
	}
}

OpenGLVertexLayout::~OpenGLVertexLayout()
{
	glDeleteVertexArrays(1, &m_LayoutID);
}

void OpenGLVertexLayout::Bind()
{
	glBindVertexArray(m_LayoutID);
}

void OpenGLVertexLayout::Unbind()
{
	glBindVertexArray(0);
}
