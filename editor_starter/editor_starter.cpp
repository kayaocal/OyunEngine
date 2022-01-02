#include "Editor.h"
#include <EditorGameSubsystem.h>
#include <subsystems/RenderSubsystem.h>
#include <subsystems/WorldSubsystem.h>
#include <subsystems/LogSubsystem.h>
#include <subsystems/ResourceSubsystem.h>

#include <EngineGlfwHandler.h>
#include <subsystems/InputSubsystem.h>

Editor::Editor* gEditorEngine;

int main()
{
	using namespace Oyun;


	Oyun::LogSubsystem::Instantiate().StartUp();
	Oyun::ResourceSubsystem::Instantiate().StartUp();
	Oyun::InitializeRenderer();
	

	gEditorEngine = new Editor::Editor(new Editor::EditorGameSubsystem(), 
		new Oyun::RenderSubsystem(1366, 768), new Oyun::WorldSubsystem());

	
	gEditorEngine->StartUp();


	while(gEditorEngine->engineRunning)
	{
		gEditorEngine->Loop();

		auto iterator = std::remove_if(gEditorEngine->subEngineInstances.begin(), gEditorEngine->subEngineInstances.end(), [&](Oyun::Engine* eng)
			{
				if (!eng->engineRunning)
				{
					eng->ShutDown();
					delete eng;
					return true;
				}
				return false;
			});
		gEditorEngine->subEngineInstances.erase(iterator, gEditorEngine->subEngineInstances.end());

		for (auto m : gEditorEngine->subEngineInstances)
		{
			if (m->engineRunning)
			{
				m->Loop();
			}
		}
		PollWindowEvents();

	}



	for (auto m : gEditorEngine->subEngineInstances)
	{
		m->ShutDown();
	}
	gEditorEngine->ShutDown();

	Oyun::ResourceSubsystem::Get().ShutDown();
	Oyun::LogSubsystem::Get().ShutDown();

	return 0;
}