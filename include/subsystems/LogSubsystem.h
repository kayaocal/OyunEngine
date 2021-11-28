#ifndef OYUN_LOG_SUBSYSTEM_H__
#define OYUN_LOG_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <memory>
#include <iosfwd>
#include <ostream>
#include <sstream>


#define LOG LogSubsystem::Get()
#define END std::endl

namespace Oyun
{
	class EngineExport LogSubsystem : public EngineSubsytem<LogSubsystem>
	{
		LogSubsystem();
		~LogSubsystem();

		std::ostringstream oss;

	public:

		static LogSubsystem* system;

		static LogSubsystem* GetPtr();
		static LogSubsystem& Get();
		static LogSubsystem& Instantiate(int width = 800, int height = 600);

		template <typename T>
		LogSubsystem& operator<<(T a)
		{
			oss << a;
			return *this;
		}

		LogSubsystem& LogSubsystem::operator<<(std::ostream& (*f)(std::ostream&));

		virtual void StartUp() override;
		virtual void ShutDown() override;


	private:
		std::unique_ptr<std::ofstream> mfileStreamPtr;

	};

}

#endif //OYUN_LOG_SUBSYSTEM_H__