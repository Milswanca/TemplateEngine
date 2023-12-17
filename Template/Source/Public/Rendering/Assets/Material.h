#pragma once
#include "Core/Object.h"
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

class RHIShaderProgram;
class RHITexture;

class Material : public Object
{
public:
	enum class ParameterTypes
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Mat4
	};

	struct CachedParameter
	{
		std::string m_Name;
		char* m_Bytes;
		unsigned int m_Size;
		ParameterTypes m_Type;
	};
	typedef std::unordered_map<std::string, Material::CachedParameter*> MaterialParameterMap;

public:
	static Material* Create(RHIShaderProgram* InShader);

protected:
	IMPLEMENT_CONSTRUCTOR(Material, Object);

	virtual void End() override;

public:
	void Bind();
	void Unbind();

	void SetInt(const std::string& InName, const int InValue);
	void SetFloat(const std::string& InName, const float InValue);
	void SetVector2(const std::string& InName, const glm::vec2& InValue);
	void SetVector3(const std::string& InName, const glm::vec3& InValue);
	void SetVector4(const std::string& InName, const glm::vec4& InValue);
	void SetMat4(const std::string& InName, const glm::mat4& InValue);
	void SetTexture(const std::string& InName, RHITexture* InValue);

	bool GetInt(const std::string& InName, int& OutValue) const;
	bool GetFloat(const std::string& InName, float& OutValue) const;
	bool GetVector2(const std::string& InName, glm::vec2& OutValue) const;
	bool GetVector3(const std::string& InName, glm::vec3& OutValue) const;
	bool GetVector4(const std::string& InName, glm::vec4& OutValue) const;
	bool GetMat4(const std::string& InName, glm::mat4& OutValue) const;
	bool GetTexture(const std::string& InName, RHITexture*& OutValue) const;

	void SetShader(RHIShaderProgram* InShader);
	RHIShaderProgram* GetShader() const;

private:
	CachedParameter* GetCachedParameter(std::string InName) const;
	CachedParameter* GetOrCreateCachedParameter(std::string InName, int InSizeBytes);

	int FindTextureParamIndex(const std::string& InName) const;
	void BindTextures();
	void UnbindTextures();

	RHITexture* m_Textures[32];
	std::string m_TextureParamNames[32];
	unsigned int m_NumTextureParams = 0;

	RHIShaderProgram* m_Shader;
	MaterialParameterMap m_Parameters;
};