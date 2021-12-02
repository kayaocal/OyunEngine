#ifndef OYUN_SHADER_H__
#define OYUN_SHADER_H__

#include <map>
#include <string>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{

	class OYUN_API Shader
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

	class OYUN_API ShaderStore
	{
	public:
		ShaderStore();

		std::map<uint32_t, Shader*> shaderPrograms;

		Shader* CompileShader(uint32_t shaderCode, const char* vertexShader, const char* fragmentShader);

		Shader* GetShader(uint32_t shaderCode);



		void DeleteShaders();
	};
}

#endif OYUN_SHADER_H__