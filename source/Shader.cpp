#include "..\include\Shader.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma once

namespace Engine
{

	ShaderManager::ShaderManager()
	{
	}

	ShaderManager& ShaderManager::Get()
	{
		static ShaderManager shader;
		return shader;
		// TODO: insert return statement here
	}

	void ShaderManager::CompileShader(const char* shaderName, const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		std::cout << "Compile Shader : " << shaderName << std::endl;

		//Vertex
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Fragment
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			ShaderPrograms.insert(std::pair<std::string, Shader*>(shaderName, new Shader(shaderProgram)));
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	Shader* ShaderManager::GetShaderByName(const char* shaderName)
	{
		auto program = ShaderPrograms.find(shaderName);
		if (program != ShaderPrograms.end())
		{
			return program->second;
		}

		return nullptr;
	}

	void ShaderManager::DeleteShaders()
	{
		for (auto itr = ShaderPrograms.begin(); itr != ShaderPrograms.end(); ++itr)
		{
			delete itr->second;
		}

		ShaderPrograms.erase(ShaderPrograms.begin(), ShaderPrograms.end());
	}

	Shader::Shader(unsigned int value)
	{
		ProgramId = value;
	}

	Shader::~Shader()
	{
		glDeleteProgram(ProgramId);
	}

	void Shader::Use()
	{
		glUseProgram(ProgramId);

	}

	void Shader::SetBool(const char* uniformName, bool value) const
	{
		glUniform1i(glGetUniformLocation(ProgramId, uniformName), (int)value);
	}

	void Shader::SetInt(const char* uniformName, int value) const
	{
		glUniform1i(glGetUniformLocation(ProgramId, uniformName), value);
	}

	void Shader::SetFloat(const char* uniformName, float value) const
	{
		glUniform1f(glGetUniformLocation(ProgramId, uniformName), value);
	}

	void Shader::SetMat4(const char* uniformName, float value) const
	{
	}

}