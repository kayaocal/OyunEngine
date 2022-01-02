#pragma once
#include <Subsystems\GameSubsystem.h>
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
	public:
		
		EditorGameSubsystem();
		virtual ~EditorGameSubsystem();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void GameLoop(float deltaTime);

		Oyun::Cameraman* EditorDefaultCameraman;

	private:

		void CreateUIElements();

		
	};
}