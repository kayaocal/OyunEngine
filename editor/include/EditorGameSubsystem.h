#pragma once
#include "GameSubsystem.h"

namespace Oyun
{
	struct Cameraman;
}

namespace Editor
{
	class EngineExport EditorGameSubsystem : public Oyun::GameSubsystem
	{
	protected:
		EditorGameSubsystem();
		virtual ~EditorGameSubsystem();


	public:

		static EditorGameSubsystem* system;

		static EditorGameSubsystem* GetPtr();
		static EditorGameSubsystem& Get();
		static EditorGameSubsystem& Instantiate();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void GameLoop(float deltaTime);

		Oyun::Cameraman* EditorDefaultCameraman;

	private:

		void CreateUIElements();

		
	};
}