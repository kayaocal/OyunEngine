#include "EditorGameSubsystem.h"
#include <subsystems/LogSubsystem.h>
#include <subsystems/RenderSubsystem.h>
#include <EngineGlfwImguiHandler.h>
#include <EditorImLayer.h>
#include <CameraManager.h>
#include <Camera.h>
#include <Entity.h>
#include <components\TransformComponent.h>

namespace Editor
{

	EditorGameSubsystem* EditorGameSubsystem::system = nullptr;

	EditorGameSubsystem::EditorGameSubsystem()
		:GameSubsystem(), EditorDefaultCameraman{ nullptr }
	{
		GameName = "Oyun Editor";
		GameVersion = "v0.0.0.1d";
	}

	EditorGameSubsystem::~EditorGameSubsystem()
	{
		system = nullptr;
	}

	EditorGameSubsystem* EditorGameSubsystem::GetPtr()
	{
		return system;
	}

	EditorGameSubsystem& EditorGameSubsystem::Get()
	{
		return *system;
	}

	EditorGameSubsystem& EditorGameSubsystem::Instantiate()
	{
		using namespace Oyun;
		
		//Oyun::ASSERT(system == nullptr, "EditorGameSubsystem can't initialize" );
		system = new EditorGameSubsystem();
		return *system;
	}

	void EditorGameSubsystem::StartUp()
	{
		GameSubsystem::StartUp();

		using namespace Oyun;
		LOG << "EditorGameSubsystem Startup" << END;

		EditorDefaultCameraman = Oyun::CreateCameraman(glm::vec3(0.0f, 0.0f, 10.0f));
		EditorDefaultCameraman->isActive = true;
		CreateUIElements();
	}

	void EditorGameSubsystem::ShutDown()
	{
		using namespace Oyun;
		LOG << "EditorGameSubsystem Shutdown" << END;
		delete this;
	}

	void EditorGameSubsystem::GameLoop(float deltaTime)
	{
		GameSubsystem::GameLoop(deltaTime);
		using namespace Oyun;

	}

	void EditorGameSubsystem::CreateUIElements()
	{
		using namespace Editor;
		using namespace Oyun;

		Imgui::AddLayer(new EditorDockableWindowLayer("DockWnd"));
		Imgui::AddLayer(new EditorPropertiesLayer("Properties"));
		Imgui::AddLayer(new EditorViewPortLayer("Viewport", EditorDefaultCameraman->camera));
	/*	 Oyun::Cameraman* cam = Oyun::CreateCameraman(glm::vec3(0.0f));
		 cam->isActive = true;
		AddLayer(new EditorViewPortLayer("Viewport2", cam->camera));
		Oyun::Cameraman* cam2 = Oyun::CreateCameraman(glm::vec3(0.0f));
		cam2->isActive = true;
		AddLayer(new EditorViewPortLayer("Viewport3", cam2->camera));*/

		Imgui::AddLayer(new EditorSceneLayer("Scene"));
	}
}