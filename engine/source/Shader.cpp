#include "..\include\Shader.h"
#include "subsystems/LogSubsystem.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma once

namespace Oyun
{

	ShaderStore::ShaderStore()
	{
	}

	Shader* ShaderStore::CompileShader(uint32_t shaderCode, const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		LOG << "Compile Shader : " << shaderCode;

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
			LOG << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
		}

		//Fragment
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			LOG << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
		}

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			LOG << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
			return nullptr;
		}
		else
		{
			Shader* sh = new Shader(shaderProgram);
			shaderPrograms.insert(std::pair<uint32_t, Shader*>(shaderCode, sh));
			return sh;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	Shader* ShaderStore::GetShader(uint32_t shaderName)
	{
		auto program = shaderPrograms.find(shaderName);
		if (program != shaderPrograms.end())
		{
			return program->second;
		}

		return nullptr;
	}

	void ShaderStore::DeleteShaders()
	{
		for (auto itr = shaderPrograms.begin(); itr != shaderPrograms.end(); ++itr)
		{
			delete itr->second;
		}

		shaderPrograms.erase(shaderPrograms.begin(), shaderPrograms.end());
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