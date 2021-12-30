#include "subsystems/LogSubsystem.h"
#include "Engine.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <fstream>

namespace Oyun
{
	std::ostringstream oss;
	bool shouldPrintEndl = false;
	LogSubsystem* LogSubsystem::system = nullptr;

	LogSubsystem::LogSubsystem()
		:EngineSubsytem()
	{
	}

	LogSubsystem::~LogSubsystem()
	{
	}

	LogSubsystem* LogSubsystem::GetPtr()
	{

		return system;
	}

	LogSubsystem& LogSubsystem::Get()
	{
		shouldPrintEndl = true;
		return *system;
	}

	LogSubsystem& LogSubsystem::Instantiate()
	{
		assert(system == nullptr);
		system = new LogSubsystem();
		return *system;
	}

	std::string day[] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
	};

	void LogSubsystem::StartUp()
	{
		mfileStreamPtr = std::unique_ptr<std::ofstream>(new std::ofstream("Log.log", std::ios::out));
		assert(mfileStreamPtr->is_open());
		mfileStreamPtr->close();

		std::stringstream stream;
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		tm local_tm = *localtime(&time);
		*LogSubsystem::GetPtr() << "LogSubsystem Started at " << local_tm.tm_mday << "."<<local_tm.tm_mon << "." << local_tm.tm_year+1900<<" - " << day[local_tm.tm_wday];

	}

	void LogSubsystem::ShutDown()
	{
		std::stringstream stream;
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		LOG << "LogSubsystem Shutdown ";
		delete this;
	}

	void LogSubsystem::PrintLog()
	{
		std::stringstream stream;
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		tm local_tm = *localtime(&time);

		if (shouldPrintEndl)
		{
			stream << std::endl;
			shouldPrintEndl = false;
			stream << "[" << local_tm.tm_hour << ":" << local_tm.tm_min
				<< ":" << local_tm.tm_sec << "][" << gFrameCount << "] -";
		}

		stream << oss.str();


		std::cout << stream.str();
		if (!mfileStreamPtr->is_open())
		{
			mfileStreamPtr->open("Log.log", std::ios::app);
		}
		*mfileStreamPtr << stream.str();
		mfileStreamPtr->close();
		oss.str("");
	}
	
	LogSubsystem& LogSubsystem::operator<<(std::ostream& (*f)(std::ostream&))
	{
		return *this;
		/*if (f == std::endl)
		{
			std::stringstream stream;
			auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			tm local_tm = *localtime(&time);

			stream << "[" << local_tm.tm_hour << ":" << local_tm.tm_min
				<< ":" << local_tm.tm_sec << "]["<<gFrameCount <<"] -" << oss.str() << std::endl;

			std::cout << stream.str();
			if (!mfileStreamPtr->is_open())
			{
				mfileStreamPtr->open("Log.log", std::ios::app);
			}
			*mfileStreamPtr << stream.str();
			mfileStreamPtr->close();
			oss.str("");
		}
		return *this;*/
	}

}

