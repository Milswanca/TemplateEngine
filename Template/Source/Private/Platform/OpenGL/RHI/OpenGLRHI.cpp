#include "Platform/OpenGL/RHI/OpenGLRHI.h"

RHI* CreateRHI()
{
	return new OpenGLRHI();
}

std::unordered_map<BufferTypes, GLenum> OpenGLRHI::s_BufferTypesToGLTypes =
{
	{ BufferTypes::ColorBuffer, GL_COLOR_BUFFER_BIT },
	{ BufferTypes::DepthBuffer, GL_DEPTH_BUFFER_BIT }
};

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),  type, severity, message );
}

OpenGLRHI::OpenGLRHI() : RHI()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

OpenGLRHI::~OpenGLRHI()
{
	
}

void OpenGLRHI::RHISetViewport(int InX, int InY, int InWidth, int InHeight)
{
	glViewport(InX, InY, InWidth, InHeight);
}

void OpenGLRHI::RHIBeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

void OpenGLRHI::RHIEndFrame()
{
	
}

void OpenGLRHI::RHIDrawElements(int InNumIndices, int InOffset)
{
	glDrawElements(GL_TRIANGLES, InNumIndices, GL_UNSIGNED_INT, 0);
}

RHIShaderProgram* OpenGLRHI::RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader)
{
	OpenGLShaderProgram* Program = new OpenGLShaderProgram();
	Program->SetVertexShader(dynamic_cast<OpenGLVertexShader*>(InVertexShader));
	Program->SetPixelShader(dynamic_cast<OpenGLPixelShader*>(InPixelShader));
	Program->LinkProgram();

	return Program;
}

void OpenGLRHI::RHIUseShaderProgram(RHIShaderProgram* InProgram)
{
	OpenGLShaderProgram* Program = static_cast<OpenGLShaderProgram*>(InProgram);
	Program->Use();
}

void OpenGLRHI::RHIDeleteShaderProgram(RHIShaderProgram* InProgram)
{
	delete InProgram;
	InProgram = nullptr;
}

RHIVertexShader* OpenGLRHI::RHICreateVertexShader(std::string_view InSource)
{
	OpenGLVertexShader* Shader = new OpenGLVertexShader();
	RHISetOpenGLShaderSource(Shader, InSource);
	return Shader;
}

RHIPixelShader* OpenGLRHI::RHICreatePixelShader(std::string_view InSource)
{
	OpenGLPixelShader* Shader = new OpenGLPixelShader();
	RHISetOpenGLShaderSource(Shader, InSource);
	return Shader;
}

void OpenGLRHI::RHISetOpenGLShaderSource(OpenGLShader* InShader, std::string_view InSource)
{
	InShader->SetShaderSource(InSource);
	InShader->Compile();
}

void OpenGLRHI::RHIDeleteShader(RHIShader* InShader)
{
	delete InShader;
	InShader = nullptr;
}

RHITexture* OpenGLRHI::RHICreateTexture(const CreateTextureDesc& InDesc)
{
	OpenGLTexture* Texture = new OpenGLTexture(InDesc);
	return Texture;
}

void OpenGLRHI::RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory)
{
	OpenGLTexture* OGLTexture = static_cast<OpenGLTexture*>(InTexture);
	OGLTexture->SetPixelData(InRawMemory);
}

void OpenGLRHI::RHIDeleteTexture(RHITexture* InTexture)
{
	delete InTexture;
	InTexture = nullptr;
}

RHIVertexStateObject* OpenGLRHI::RHICreateVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes)
{
	OpenGLVertexStateObject* StateObject = new OpenGLVertexStateObject(InVertexBuffer, InIndexBuffer, InAttributes);
	return StateObject;
}

void OpenGLRHI::RHIRebuildVertexStateObject(RHIVertexStateObject* InStateObject)
{
	OpenGLVertexStateObject* StateObject = static_cast<OpenGLVertexStateObject*>(InStateObject);
	StateObject->Rebuild();
}

void OpenGLRHI::RHIBindVertexStateObject(RHIVertexStateObject* InStateObject)
{
	OpenGLVertexStateObject* StateObject = static_cast<OpenGLVertexStateObject*>(InStateObject);
	StateObject->Bind();
}

void OpenGLRHI::RHIDeleteVertexStateObject(RHIVertexStateObject* InStateObject)
{
	delete InStateObject;
	InStateObject = nullptr;
}

RHIVertexBuffer* OpenGLRHI::RHICreateVertexBuffer(const RHIBufferDesc& InDesc)
{
	return new OpenGLVertexBuffer(InDesc);
}

RHIIndexBuffer* OpenGLRHI::RHICreateIndexBuffer(const RHIBufferDesc& InDesc)
{
	return new OpenGLIndexBuffer(InDesc);
}

void* OpenGLRHI::RHIMapBuffer(RHIBuffer* InBuffer, BufferAccessTypes InAccess)
{
	OpenGLBuffer* OGLBuffer = dynamic_cast<OpenGLBuffer*>(InBuffer);
	return OGLBuffer->Map(InAccess);
}

void OpenGLRHI::RHIUnmapBuffer(RHIBuffer* InBuffer)
{
	OpenGLBuffer* OGLBuffer = dynamic_cast<OpenGLBuffer*>(InBuffer);
	OGLBuffer->Unmap();
}

void OpenGLRHI::RHIBindBuffer(RHIBuffer* InBuffer)
{
	OpenGLBuffer* OGLBuffer = dynamic_cast<OpenGLBuffer*>(InBuffer);
	OGLBuffer->Bind();
}

void OpenGLRHI::RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, void* InData)
{
	OpenGLBuffer* OGLBuffer = dynamic_cast<OpenGLBuffer*>(InBuffer);
	OGLBuffer->BufferSubData(InSizeBytes, InOffsetBytes, InData);
}

void OpenGLRHI::RHIDeleteBuffer(RHIBuffer* InBuffer)
{
	delete InBuffer;
	InBuffer = nullptr;
}