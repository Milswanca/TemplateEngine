#include "Rendering/Material.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Core/Engine.h"
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.inl>

Material* Material::Create(Shader* InShader)
{
	Material* NewMaterial = Engine::Get()->NewObject<Material>();
	NewMaterial->SetShader(InShader);
	return NewMaterial;
}

void Material::End()
{
	Object::End();

	for (auto Iter : m_Parameters)
	{
		delete[] Iter.second->m_Bytes;
	}
}

void Material::Bind()
{
	if (m_Shader == nullptr)
		return;

	glUseProgram(m_Shader->GetProgramID());

	for (auto Iter : m_Parameters)
	{
		int Loc = m_Shader->GetParameterLocation(Iter.first);

		switch (Iter.second->m_Type)
		{
		case ParameterTypes::Int:
			glUniform1i(Loc, *(GLint*)(Iter.second->m_Bytes));
			break;

		case ParameterTypes::Float:
			glUniform1f(Loc, *(GLfloat*)(Iter.second->m_Bytes));
			break;

		case ParameterTypes::Vector2:
			glUniform2fv(Loc, 1, (GLfloat*)Iter.second->m_Bytes);
			break;

		case ParameterTypes::Vector3:
			glUniform3fv(Loc, 1, (GLfloat*)Iter.second->m_Bytes);
			break;

		case ParameterTypes::Vector4:
			glUniform4fv(Loc, 1, (GLfloat*)Iter.second->m_Bytes);
			break;

		case ParameterTypes::Mat4:
			glUniformMatrix4fv(Loc, 1, GL_FALSE, (GLfloat*)Iter.second->m_Bytes);
			break;
		}
	}

	BindTextures();
}

void Material::Unbind()
{
	if (m_Shader == nullptr)
		return;

	glUseProgram(0);
	glm::mat4 EmptyMatrix = glm::identity<glm::mat4>();

	for (auto Iter = m_Parameters.begin(); Iter != m_Parameters.end(); ++Iter)
	{
		CachedParameter* Parameter = Iter->second;
		int Loc = m_Shader->GetParameterLocation(Parameter->m_Name);

		switch (Parameter->m_Type)
		{
		case ParameterTypes::Int:
			glUniform1i(Loc, 0);
			break;

		case ParameterTypes::Float:
			glUniform1f(Loc, 0.0f);
			break;

		case ParameterTypes::Vector2:
			glUniform2f(Loc, 0.0f, 0.0f);
			break;

		case ParameterTypes::Vector3:
			glUniform3f(Loc, 0.0f, 0.0f, 0.0f);
			break;

		case ParameterTypes::Vector4:
			glUniform4f(Loc, 0.0f, 0.0f, 0.0f, 0.0f);
			break;

		case ParameterTypes::Mat4:
			glUniformMatrix4fv(Loc, 1, GL_FALSE, (GLfloat*)&EmptyMatrix);
			break;
		}
	}

	UnbindTextures();
}

void Material::BindTextures()
{
	for (unsigned int i = 0; i < m_NumTextureParams; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i]->GetTextureID());

		unsigned int Loc = m_Shader->GetParameterLocation(m_TextureParamNames[i]);
		glUniform1i(Loc, i);
	}
}

void Material::UnbindTextures()
{
	for (unsigned int i = 0; i < m_NumTextureParams; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);

		unsigned int Loc = m_Shader->GetParameterLocation(m_TextureParamNames[i]);
		glUniform1i(Loc, 0);
	}
}

void Material::SetInt(const std::string& InName, const int InValue)
{
	CachedParameter* Param = GetOrCreateCachedParameter(InName, sizeof(int));
	memcpy(Param->m_Bytes, &InValue, sizeof(int));
	Param->m_Size = sizeof(int);
	Param->m_Type = ParameterTypes::Int;
}

void Material::SetFloat(const std::string& InName, const float InValue)
{
	CachedParameter* Param = GetOrCreateCachedParameter(InName, sizeof(float));
	memcpy(Param->m_Bytes, &InValue, sizeof(float));
	Param->m_Size = sizeof(float);
	Param->m_Type = ParameterTypes::Float;
}

void Material::SetVector2(const std::string& InName, const glm::vec2& InValue)
{
	CachedParameter* Param = GetOrCreateCachedParameter(InName, sizeof(glm::vec2));
	memcpy(Param->m_Bytes, &InValue, sizeof(glm::vec2));
	Param->m_Size = sizeof(glm::vec2);
	Param->m_Type = ParameterTypes::Vector2;
}

void Material::SetVector3(const std::string& InName, const glm::vec3& InValue)
{
	CachedParameter* Param = GetOrCreateCachedParameter(InName, sizeof(glm::vec3));
	memcpy(Param->m_Bytes, &InValue, sizeof(glm::vec3));
	Param->m_Size = sizeof(glm::vec3);
	Param->m_Type = ParameterTypes::Vector3;
}

void Material::SetVector4(const std::string& InName, const glm::vec4& InValue)
{
	CachedParameter* Param = GetOrCreateCachedParameter(InName, sizeof(glm::vec4));
	memcpy(Param->m_Bytes, &InValue, sizeof(glm::vec4));
	Param->m_Size = sizeof(glm::vec4);
	Param->m_Type = ParameterTypes::Vector4;
}

void Material::SetMat4(const std::string& InName, const glm::mat4& InValue)
{
	CachedParameter* Param = GetOrCreateCachedParameter(InName, sizeof(glm::mat4));
	memcpy(Param->m_Bytes, &InValue, sizeof(glm::mat4));
	Param->m_Size = sizeof(glm::mat4);
	Param->m_Type = ParameterTypes::Mat4;
}

void Material::SetTexture(const std::string& InName, Texture* InValue)
{
	int Index = FindTextureParamIndex(InName);
	if (Index != -1)
	{
		m_Textures[Index] = m_Textures[m_NumTextureParams - 1];
		m_TextureParamNames[Index] = m_TextureParamNames[m_NumTextureParams - 1];
		m_NumTextureParams--;
	}

	if (InValue != nullptr)
	{
		m_Textures[m_NumTextureParams] = InValue;
		m_TextureParamNames[m_NumTextureParams] = InName;
		m_NumTextureParams++;
	}
}

bool Material::GetInt(const std::string& InName, int& OutValue) const
{
	if (CachedParameter* Param = GetCachedParameter(InName))
	{
		memcpy(&OutValue, Param->m_Bytes, sizeof(int));
		return true;
	}

	return false;
}

bool Material::GetFloat(const std::string& InName, float& OutValue) const
{
	if (CachedParameter* Param = GetCachedParameter(InName))
	{
		memcpy(&OutValue, Param->m_Bytes, sizeof(float));
		return true;
	}

	return false;
}

bool Material::GetVector2(const std::string& InName, glm::vec2& OutValue) const
{
	if (CachedParameter* Param = GetCachedParameter(InName))
	{
		memcpy(&OutValue, Param->m_Bytes, sizeof(glm::vec2));
		return true;
	}

	return false;
}

bool Material::GetVector3(const std::string& InName, glm::vec3& OutValue) const
{
	if (CachedParameter* Param = GetCachedParameter(InName))
	{
		memcpy(&OutValue, Param->m_Bytes, sizeof(glm::vec3));
		return true;
	}

	return false;
}

bool Material::GetVector4(const std::string& InName, glm::vec4& OutValue) const
{
	if (CachedParameter* Param = GetCachedParameter(InName))
	{
		memcpy(&OutValue, Param->m_Bytes, sizeof(glm::vec4));
		return true;
	}

	return false;
}

bool Material::GetMat4(const std::string& InName, glm::mat4& OutValue) const
{
	if (CachedParameter* Param = GetCachedParameter(InName))
	{
		memcpy(&OutValue, Param->m_Bytes, sizeof(glm::mat4));
		return true;
	}

	return false;
}

bool Material::GetTexture(const std::string& InName, Texture*& OutValue) const
{
	int Index = FindTextureParamIndex(InName);

	if (Index != -1)
	{
		OutValue = m_Textures[Index];
	}

	return Index != -1;
}

void Material::SetShader(Shader* InShader)
{
	m_Shader = InShader;
}

Shader* Material::GetShader() const
{
	return m_Shader;
}

Material::CachedParameter* Material::GetCachedParameter(std::string InName) const
{
	auto Iter = m_Parameters.find(InName);
	return Iter != m_Parameters.end() ? (*Iter).second : nullptr;
}

Material::CachedParameter* Material::GetOrCreateCachedParameter(std::string InName, int InSizeBytes)
{
	CachedParameter* ExistingParam = GetCachedParameter(InName);
	
	if (!ExistingParam)
	{
		ExistingParam = new CachedParameter();
		ExistingParam->m_Name = InName;
		ExistingParam->m_Bytes = new char[InSizeBytes];
		m_Parameters[InName] = ExistingParam;
	}

	return ExistingParam;
}

int Material::FindTextureParamIndex(const std::string& InName) const
{
	for (size_t i = 0; i < m_NumTextureParams; ++i)
	{
		if (InName == m_TextureParamNames[i])
		{
			return i;
		}
	}

	return -1;
}