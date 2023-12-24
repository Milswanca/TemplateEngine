#pragma once
#include "Rendering/RHI/RHI.h"
#include "Platform/OpenGL/RHI/Resources/OpenGLShader.h"
#include "Platform/OpenGL/RHI/Resources/OpenGLShaderProgram.h"
#include "Platform/OpenGL/RHI/Resources/OpenGLTexture.h"
#include "Platform/OpenGL/RHI/Resources/OpenGLBuffer.h"
#include "Platform/OpenGL/RHI/Resources/OpenGLVertexStateObject.h"
#include <glad/glad.h>
#include <unordered_map>

class OpenGLRHI : public RHI
{
public:
	OpenGLRHI();
	~OpenGLRHI();

	void RHIBeginFrame() override;
	void RHIEndFrame() override;
	void RHISetViewport(int InX, int InY, int InWidth, int InHeight) override;
	void RHIDrawElements(int InNumIndices, int InOffset) override;
	
	RHIShaderProgram* RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader) override;
	void RHIUseShaderProgram(RHIShaderProgram* InProgram) override;
	void RHIDeleteShaderProgram(RHIShaderProgram* InProgram) override;

	RHIVertexShader* RHICreateVertexShader(std::string_view InSource) override;
	RHIPixelShader* RHICreatePixelShader(std::string_view InSource) override;
	void RHISetOpenGLShaderSource(OpenGLShader* InShader, std::string_view InSource);
	void RHIDeleteShader(RHIShader* InShader) override;

	RHITexture* RHICreateTexture(const CreateTextureDesc& InDesc) override;
	void RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory) override;
	void RHIDeleteTexture(RHITexture* InTexture) override;

	RHIVertexStateObject* RHICreateVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes) override;
	void RHIRebuildVertexStateObject(RHIVertexStateObject* InStateObject) override;
	void RHIBindVertexStateObject(RHIVertexStateObject* InStateObject) override;
	void RHIDeleteVertexStateObject(RHIVertexStateObject* InStateObject) override;
	RHIVertexBuffer* RHICreateVertexBuffer(const RHIBufferDesc& InDesc) override;
	RHIIndexBuffer* RHICreateIndexBuffer(const RHIBufferDesc& InDesc) override;
	void* RHIMapBuffer(RHIBuffer* InBuffer, BufferAccessTypes InAccess) override;
	void RHIUnmapBuffer(RHIBuffer* InBuffer) override;
	void RHIBindBuffer(RHIBuffer* Buffer) override;
	void RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, void* InData) override;
	void RHIDeleteBuffer(RHIBuffer* InBuffer) override;

private:
	static std::unordered_map<BufferTypes, GLenum> s_BufferTypesToGLTypes;
};