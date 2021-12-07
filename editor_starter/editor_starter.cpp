#include <Engine.h>
#include <EditorGameSubsystem.h>
#include <subsystems/RenderSubsystem.h>
#include <subsystems/WorldSubsystem.h>
#include <subsystems/LogSubsystem.h>
#include <subsystems/ResourceSubsystem.h>
Oyun::Engine* gEditorEngine;

int main()
{
	using namespace Oyun;

	Oyun::LogSubsystem::Instantiate().StartUp();
	Oyun::ResourceSubsystem::Instantiate().StartUp();

	gEditorEngine = new Oyun::Engine(new Editor::EditorGameSubsystem(), 
		new Oyun::RenderSubsystem(1366, 768), new Oyun::WorldSubsystem());
	
	gEditorEngine->StartUp();

	while(gEditorEngine->engineRunning)
	{
		gEditorEngine->Loop();
	}

	gEditorEngine->ShutDown();
	Oyun::ResourceSubsystem::Get().ShutDown();
	Oyun::LogSubsystem::Get().ShutDown();
	
	return 0;
}