#pragma once
#include <subsystems\GameSubsystem.h>
#define EDITOR_API 

namespace Oyun
{
	struct Cameraman;
}

namespace Editor
{
	class EDITOR_API FloatingCubesGameSubsystem : public Oyun::GameSubsystem
	{
	protected:
		FloatingCubesGameSubsystem();
		virtual ~FloatingCubesGameSubsystem();


	public:

		static FloatingCubesGameSubsystem* system;

		static FloatingCubesGameSubsystem* GetPtr();
		static FloatingCubesGameSubsystem& Get();
		static FloatingCubesGameSubsystem& Instantiate();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void GameLoop(float deltaTime);


		
	};
}