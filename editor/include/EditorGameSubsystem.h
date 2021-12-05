#pragma once
#include <subsystems\GameSubsystem.h>
#ifdef OyunEditor_EXPORTS
#define EDITOR_API __declspec(dllexport)
#else
#define EDITOR_API __declspec(dllimport)
#endif

namespace Oyun
{
	struct Cameraman;
}

namespace Editor
{
	class EDITOR_API EditorGameSubsystem : public Oyun::GameSubsystem
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