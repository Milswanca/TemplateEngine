#pragma once
#include "Core/Object.h"
#include "Rendering/Material.h"
#include <glad/glad.h>
#include <unordered_map>

enum class EShaderTypes
{
	Unknown,
	Vertex,
	Fragment,
	TessControl,
	TessEval,
	COUNT
};

class Shader : public Object
{
public:
	struct FShaderParameterCache
	{
		std::string m_ParameterName;
		int m_ParameterLocation;
	};
	typedef std::unordered_map<std::string, FShaderParameterCache> FShaderParameterMap;

public:
	struct FCreateShaderParams
	{
		FCreateShaderParams()
		{
			m_VertexShader = "";
			m_FragmentShader = "";
			m_TessControlShader = "";
			m_TessEvalShader = "";
		}

		std::string m_VertexShader;
		std::string m_FragmentShader;
		std::string m_TessControlShader;
		std::string m_TessEvalShader;
	};

	static Shader* Create(const FCreateShaderParams& Params);

protected:
	IMPLEMENT_CONSTRUCTOR(Shader, Object);

	virtual void Begin() override;
	virtual void End() override;

public:
	void AddShader(EShaderTypes InType, const std::string& InSource);
	void RemoveShader(EShaderTypes InType);
	void Compile();
	bool HasShaderType(EShaderTypes InType) const;

	unsigned int GetProgramID() const;
	int GetParameterLocation(const std::string& InName) const;

private:
	bool LoadShaderProgram(const std::string& InSource, std::string& InContents) const;
	void CacheParameters();

	int m_ShaderFlags;

	unsigned int m_ShaderIDs[static_cast<int>(EShaderTypes::COUNT)];
	std::string m_ShaderSources[static_cast<int>(EShaderTypes::COUNT)];

	unsigned int m_ProgramID;
	FShaderParameterMap m_Parameters;
};