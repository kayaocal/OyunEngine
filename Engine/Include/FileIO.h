#ifndef FILE_IO_H__
#define FILE_IO_H__


#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <sstream>

#include <chrono>

namespace Oyun
{
	OYUN_API const wchar_t* OpenFileDialog();


	template<typename T>
	T* ReadFile(const char* path, size_t* fileSize)
	{
		using namespace std::chrono;
		auto gameLoopStart = high_resolution_clock::now();
	
		std::streampos begin, end;
		std::basic_ifstream<T> stream;

		stream.open(path, std::ifstream::binary);

		if (stream.is_open())
		{
			stream.seekg(0, stream.end);
			int length = stream.tellg();
			stream.seekg(0, stream.beg);

			T* fileBuffer = new T[length + 1];

			*fileSize = length;
			stream.read((fileBuffer), length);
			fileBuffer[length] = '\0';
			auto gameLoopEnd = high_resolution_clock::now();

			double gameTime = static_cast<double>(duration_cast<microseconds>(gameLoopEnd - gameLoopStart).count()) / 1000000.0;
			LOG << "File Read Time : " << gameTime;
			return fileBuffer;
		}

		stream.close();

		return nullptr;
	}

	OYUN_API void ReadFileSS(std::stringstream& ss, const char* path);
	
	void SaveFile(const char* path, const std::stringstream& ss);

	OYUN_API uint32_t GetHash(const std::string& str);
	
	OYUN_API uint32_t GetHash(const char* chr);

}

#endif //FILE_IO_H__
