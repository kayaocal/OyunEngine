#include "FileIO.h"

#include <sstream>
#include <Windows.h>
#include "lookup3.h"

#define MAX_FILE_NAME 256
#define MAX_FILE_TITLE 256

OPENFILENAMEW mOpenFileName;
wchar_t mFileNameBuffer[MAX_FILE_NAME];
wchar_t mFileTitleBuffer[MAX_FILE_TITLE];

const wchar_t* Oyun::OpenFileDialog()
{
	ZeroMemory(&mOpenFileName, sizeof(OPENFILENAMEW));
	mOpenFileName.lStructSize = sizeof(mOpenFileName);
	mOpenFileName.nFilterIndex = 1;
	mOpenFileName.nMaxFile = MAX_FILE_NAME;
	mOpenFileName.nMaxFileTitle = MAX_FILE_TITLE;
	mOpenFileName.lpstrFile = mFileNameBuffer;
	mOpenFileName.lpstrFileTitle = mFileTitleBuffer;
	mOpenFileName.lpstrFile[0] = '\0';
	mOpenFileName.lpstrFileTitle[0] = '\0';
	mOpenFileName.lpstrTitle = L"Select a File";
	mOpenFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	mOpenFileName.lpstrFilter = L".Any Files\0*.*";

	if (GetOpenFileNameW(&mOpenFileName))
	{
		std::wcout << "Can open requested file : " << mOpenFileName.lpstrFile << std::endl;
		return mOpenFileName.lpstrFile;
	}
	else
	{
		return nullptr;
		std::cout << "File open request failed : " << CommDlgExtendedError() << std::endl;
	}

}

void Oyun::ReadFileSS(std::stringstream& ss, const char* path)
{
	std::basic_ifstream<char> stream;
	stream.open(path, std::ifstream::in | std::ifstream::binary);

	if(stream.is_open())
	{
		ss<<stream.rdbuf();
	}

	stream.close();
}

void Oyun::SaveFile(const char* path, const std::stringstream& ss)
{
    std::fstream fs(path, std::fstream::out);
    fs << ss.rdbuf();
    fs.close();
}

uint32_t Oyun::GetHash(const std::string& str)
{
	uint32_t hash = hashlittle(str.c_str(), str.length(), 0);
	return hash;
}

uint32_t Oyun::GetHash(const char* chr)
{
	uint32_t hash = hashlittle(chr, strlen(chr), 0);
	return hash;
}



