#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLBuffer.h"

OpenGLBuffer::OpenGLBuffer(const RHIBufferDesc& InDesc, GLenum InBufferTarget, GLenum InBufferUsage) : RHIBuffer(InDesc)
{
	m_BufferTarget = InBufferTarget;
	m_BufferUsage = InBufferUsage;
	
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(m_BufferTarget, m_BufferID);
	glBufferData(m_BufferTarget, InDesc.m_Size, 0, m_BufferUsage);
}

OpenGLBuffer::~OpenGLBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void OpenGLBuffer::BufferSubData(int InSizeBytes, int InOffsetBytes, unsigned char* InData)
{
	glBindBuffer(m_BufferTarget, m_BufferID);
	glBufferSubData(m_BufferTarget, InOffsetBytes, InSizeBytes, InData);
}
