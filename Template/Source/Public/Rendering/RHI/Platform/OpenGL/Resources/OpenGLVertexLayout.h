#pragma once
#include "Rendering/RHI/Resources/RHIVertexLayout.h"
#include <unordered_map>
#include <glad/glad.h>

class OpenGLVertexLayout : public RHIVertexLayout
{
public:
	OpenGLVertexLayout(const RHIVertexAttributeArray& InAttribs);
	~OpenGLVertexLayout();

	void Bind();
	void Unbind();

protected:
	static std::unordered_map<VertexAttributeTypes, GLenum> s_VertexAttribTypeToOGL;

private:
	GLuint m_GLLayoutID;
};