#pragma once

#include <map>
#include <string>
#include "glm/glm.hpp"
#define EngineExport   __declspec( dllexport )

namespace Engine
{

	class EngineExport Shader
	{
	public:


		unsigned int ProgramId;

		explicit Shader(unsigned int);
		~Shader();
		void Use();
		void SetBool(const char* uniformName, bool value) const;
		void SetInt(const char* uniformName, int value) const;
		void SetFloat(const char* uniformName, float value) const;
		void SetMat4(const char* uniformName, float value) const;
	};

	class EngineExport ShaderManager
	{
		ShaderManager();
	public:

		static ShaderManager& Get();
		std::map<std::string, Shader*> ShaderPrograms;

		void CompileShader(const char* shaderName, const char* vertexShader, const char* fragmentShader);

		Shader* GetShaderByName(const char* shaderName);



		void DeleteShaders();
	};
}