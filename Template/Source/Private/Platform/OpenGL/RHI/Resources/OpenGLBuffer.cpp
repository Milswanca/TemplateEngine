#include "Platform/OpenGL/RHI/Resources/OpenGLBuffer.h"

std::unordered_map<BufferAccessTypes, GLenum> OpenGLBuffer::s_BufferAccessToGLTypes = {
	{ BufferAccessTypes::Read, GL_READ_ONLY },
	{ BufferAccessTypes::Write, GL_WRITE_ONLY },
	{ BufferAccessTypes::ReadWrite, GL_READ_WRITE }
};

OpenGLBuffer::OpenGLBuffer(const RHIBufferDesc& InDesc, GLenum InBufferTarget, GLenum InBufferUsage) : RHIBuffer(InDesc)
{
	m_BufferTarget = InBufferTarget;
	m_BufferUsage = InBufferUsage;
	
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(m_BufferTarget, m_BufferID);
	glBufferData(m_BufferTarget, InDesc.m_Size, nullptr, m_BufferUsage);
}

OpenGLBuffer::~OpenGLBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void OpenGLBuffer::Bind()
{
	glBindBuffer(m_BufferTarget, m_BufferID);
}

void OpenGLBuffer::Unbind()
{
	glBindBuffer(m_BufferTarget, 0);
}

void* OpenGLBuffer::Map(BufferAccessTypes InAccess)
{
	return glMapBuffer(m_BufferTarget, s_BufferAccessToGLTypes[InAccess]);
}

void OpenGLBuffer::Unmap()
{
	glUnmapBuffer(m_BufferTarget);
}

void OpenGLBuffer::BufferSubData(int InSizeBytes, int InOffsetBytes, void* InData)
{
	glBindBuffer(m_BufferTarget, m_BufferID);
	glBufferSubData(m_BufferTarget, InOffsetBytes, InSizeBytes, InData);
}
