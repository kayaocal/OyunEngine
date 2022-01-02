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
	struct Engine;
	struct Cameraman;
	class OYUN_API GameSubsystem : public EngineSubsytem<GameSubsystem>
	{
	protected:
		GameSubsystem();
		virtual ~GameSubsystem();


	public:

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void SetEngine(Engine* engine);
		virtual void GameLoop(float deltaTime);
		
		std::string GameName;
		std::string GameVersion;

		Cameraman* godCam;
		protected:
		Engine* mEngine;

	};

}

#endif //OYUN_GAME_SUBSYSTEM_H__