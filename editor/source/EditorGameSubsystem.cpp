#include "EditorGameSubsystem.h"
#include <subsystems/LogSubsystem.h>
#include <subsystems/WorldSubsystem.h>
#include <subsystems/ResourceSubsystem.h>

#include <EngineGlfwImguiHandler.h>
#include <EditorImLayer.h>
#include <CameraManager.h>
#include <Camera.h>
#include <Entity.h>
#include <ModelStore.h>
#include <components/TransformComponent.h>

#include "Engine.h"


namespace Editor
{


	EditorGameSubsystem::EditorGameSubsystem()
		:GameSubsystem(), EditorDefaultCameraman{ nullptr }
	{
		GameName = "Oyun Editor";
		GameVersion = "v0.0.0.1d";
	}

	EditorGameSubsystem::~EditorGameSubsystem()
	{
	}


	Oyun::StaticMeshEntity* ent;
	Oyun::StaticMeshEntity* ent2;
	Oyun::StaticMeshEntity* ent3;
	Oyun::StaticMeshEntity* ent4;
	void EditorGameSubsystem::StartUp()
	{
		GameSubsystem::StartUp();

		using namespace Oyun;
		LOG << "EditorGameSubsystem Startup" << END;

		EditorDefaultCameraman = Oyun::CreateCameraman(glm::vec3(0.0f, 0.0f, 10.0f));
		EditorDefaultCameraman->isActive = true;
		CreateUIElements();

		//Shader* shd = ResourceSubsystem::Get().LoadShader("testShader", 
		//	"C:\\Development\\Test\\Engine\\engine\\resources\\shaders\\simple_vertex.shader", 
		//	"C:\\Development\\Test\\Engine\\engine\\resources\\shaders\\simple_fragment.shader");
		//Model* mdl = ResourceSubsystem::Get().LoadModel("backpack.obj");
		//
		//mdl->SetShader(shd);

		//ent = new StaticMeshEntity(mdl);
		//ent->SetUniqueId(0);
		//ent2 = new StaticMeshEntity(mdl);
		//ent2->GetTransform()->Position.z = -20;
		//ent2->SetUniqueId(1);
		//ent3 = new StaticMeshEntity(mdl);
		//ent3->GetTransform()->Position.x = -10;
		//ent3->SetUniqueId(2);
		///*ent3->GetTransform()->EulerRotation.z = 90.0f;
		//ent3->GetTransform()->Position.x = 0;
		//*/
		//ent4 = new StaticMeshEntity(mdl);
		//ent4->GetTransform()->Position.x = 10.0f;
		//ent4->SetUniqueId(3);
		///*ent4->GetTransform()->Position.z = 3;
		//ent4->GetTransform()->Position.x = 3;*/

		//mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		//mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		//mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		//mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		
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
		static float angle = 0.0f;
		/*EditorDefaultCameraman->camera->Position.x = 10*sinf(angle);
		EditorDefaultCameraman->camera->Position.z = 10*cosf(angle);
		angle += deltaTime;

		ent->GetTransform()->EulerRotation.y = 180.0f * sinf(angle);
		ent3->GetTransform()->EulerRotation.z = 180.0f * sinf(angle);
		ent4->GetTransform()->EulerRotation.x = 180.0f * sinf(angle);*/
	}

	void EditorGameSubsystem::CreateUIElements()
	{
		using namespace Editor;
		using namespace Oyun;

		Imgui::AddLayer(new EditorDockableWindowLayer("DockWnd", mEngine));
		Imgui::AddLayer(new EditorPropertiesLayer("Properties", mEngine));
		Imgui::AddLayer(new EditorViewPortLayer("Viewport", mEngine, EditorDefaultCameraman->camera));
	/*	 Oyun::Cameraman* cam = Oyun::CreateCameraman(glm::vec3(0.0f));
		 cam->isActive = true;
		AddLayer(new EditorViewPortLayer("Viewport2", cam->camera));
		Oyun::Cameraman* cam2 = Oyun::CreateCameraman(glm::vec3(0.0f));
		cam2->isActive = true;
		AddLayer(new EditorViewPortLayer("Viewport3", cam2->camera));*/

		Imgui::AddLayer(new EditorSceneLayer("Scene", mEngine));
	}
}
