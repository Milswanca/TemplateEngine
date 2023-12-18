#pragma once
#include "Rendering/RHI/Resources/RHIBuffer.h"
#include <glad/glad.h>

class OpenGLBuffer : public virtual RHIBuffer
{
public:
	OpenGLBuffer(const RHIBufferDesc& InDesc, GLenum InBufferTarget, GLenum InBufferUsage);
	~OpenGLBuffer();

	void BufferSubData(int InSizeBytes, int InOffsetBytes, unsigned char* InData);

private:
	GLuint m_BufferID;
	GLenum m_BufferTarget;
	GLenum m_BufferUsage;
};

class OpenGLVertexBuffer : public RHIVertexBuffer, public OpenGLBuffer
{
public:
	OpenGLVertexBuffer(const RHIBufferDesc& InDesc) : RHIBuffer(InDesc), RHIVertexBuffer(InDesc), OpenGLBuffer(InDesc, GL_ARRAY_BUFFER, GL_STATIC_DRAW) {}
};

class OpenGLIndexBuffer : public RHIIndexBuffer, public OpenGLBuffer
{
public:
	OpenGLIndexBuffer(const RHIBufferDesc& InDesc) : RHIBuffer(InDesc), RHIIndexBuffer(InDesc), OpenGLBuffer(InDesc, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {}
};