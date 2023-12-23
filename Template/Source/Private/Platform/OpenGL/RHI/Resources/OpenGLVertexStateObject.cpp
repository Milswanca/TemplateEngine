#include "Platform/OpenGL/RHI/Resources/OpenGLVertexStateObject.h"
#include "Rendering/RHI/RHI.h"

std::unordered_map<VertexAttributeTypes, GLenum> OpenGLVertexStateObject::s_VertexAttribTypeToOGL = {
    { VertexAttributeTypes::Float, GL_FLOAT },
    { VertexAttributeTypes::Int, GL_INT },
};

OpenGLVertexStateObject::OpenGLVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes)
    : RHIVertexStateObject(InVertexBuffer, InIndexBuffer, InAttributes)
{
    glGenVertexArrays(1, &m_VertexArrayObject);
    Rebuild();
}

OpenGLVertexStateObject::~OpenGLVertexStateObject()
{
    glDeleteVertexArrays(1, &m_VertexArrayObject);
}

void OpenGLVertexStateObject::Rebuild()
{
    // Bind the VAO
    glBindVertexArray(m_VertexArrayObject);
    
    // Bind Vertex and Index buffers to the VAO
    RHIBindBuffer(GetVertexBuffer());
    RHIBindBuffer(GetIndexBuffer());

    // Apply Attributes Layout
    for(int i = 0; i < GetNumAttributes(); ++i)
    {
        const RHIVertexAttributeDesc Attrib = GetAttribute(i);
        GLenum AttribType = s_VertexAttribTypeToOGL[Attrib.m_Type];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, Attrib.m_NumChannels, AttribType, Attrib.m_bNormalize, Attrib.m_Stride, (void*)Attrib.m_Offset);
    }

    glBindVertexArray(0);
}

void OpenGLVertexStateObject::Bind()
{
    glBindVertexArray(m_VertexArrayObject);
}

void OpenGLVertexStateObject::Unbind()
{
    glBindVertexArray(0);
}
