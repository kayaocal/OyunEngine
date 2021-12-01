#ifndef OYUN_GAME_SUBSYSTEM_H__
#define OYUN_GAME_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <string>
#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	class OYUN_API GameSubsystem : public EngineSubsytem<GameSubsystem>
	{
	protected:

		GameSubsystem();
		virtual ~GameSubsystem();


	public:

		static GameSubsystem* system;

		static GameSubsystem* GetPtr();
		static GameSubsystem& Get();
		static GameSubsystem& Instantiate();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		virtual void GameLoop(float deltaTime);
		
		std::string GameName;
		std::string GameVersion;

	};

}

#endif //OYUN_GAME_SUBSYSTEM_H__