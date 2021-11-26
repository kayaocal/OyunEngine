#pragma once

#include "EngineSubsytem.h"


namespace Oyun
{
	class EngineExport GameSubsystem : public EngineSubsytem<GameSubsystem>
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
		


	};

}