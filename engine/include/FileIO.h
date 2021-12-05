#ifndef FILE_IO_H__
#define FILE_IO_H__

#include <iostream>
#include <fstream>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	template<typename T>
	OYUN_API T* ReadFile(const char* path, size_t* fileSize)
	{
		std::streampos begin, end;
		//std::ifstream stream;
		std::basic_ifstream<T> stream;

		stream.open(path, std::ifstream::in | std::ifstream::binary);

		if (stream.is_open())
		{
			stream.seekg(0, stream.end);
			int length = stream.tellg();
			stream.seekg(0, stream.beg);

			T* fileBuffer = new T[length + 1];

			*fileSize = length;
			stream.read((fileBuffer), length);
			fileBuffer[length] = '\0';
			return fileBuffer;
		}

		stream.close();

		return nullptr;
	}

}

#endif //FILE_IO_H__
