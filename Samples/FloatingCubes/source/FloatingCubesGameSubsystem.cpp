#include "FloatingCubesGameSubsystem.h"
#include <subsystems/LogSubsystem.h>
#include <subsystems/WorldSubsystem.h>
#include <CameraManager.h>
#include <Camera.h>
#include <Entity.h>
#include <subsystems/ResourceSubsystem.h>
#include <ModelStore.h>
#include <Shader.h>
#include <components/TransformComponent.h>
#include <imgui.h>
#include "Camera.h"
#include <subsystems/RenderSubsystem.h>
#include "Engine.h"
#include "EngineImGui.h"
#include "EngineGlfwHandler.h"
namespace Cubes
{


	FloatingCubesGameSubsystem::FloatingCubesGameSubsystem()
		:GameSubsystem(), mAngle(0.0f)/*, EditorDefaultCameraman{ nullptr }*/
	{
		GameName = "Floating Cubes";
		GameVersion = "v0.0.0.1d";
	}

	FloatingCubesGameSubsystem::~FloatingCubesGameSubsystem()
	{
	}


	
	void FloatingCubesGameSubsystem::StartUp()
	{
		using namespace Oyun;
		GameSubsystem::StartUp();


		LOG << "FloatingCubesGameSubsystem Startup";;

		godCam = Oyun::CreateCameraman(glm::vec3(0.0f, 0.0f, 10.0f), mEngine->GetRenderSubsystem()->GetWindow());
		godCam->isActive = true;
		mEngine->GetRenderSubsystem()->GetImGui()->AddLayer(new TestImgui("Test Window", mEngine));


		//CreateUIElements();
		Shader* shd = ResourceSubsystem::Get().LoadShader("testShader",
			"C:\\Development\\Test\\Engine\\engine\\resources\\shaders\\simple_vertex.shader",
			"C:\\Development\\Test\\Engine\\engine\\resources\\shaders\\simple_fragment.shader");
		Model* mdl = ResourceSubsystem::Get().LoadModel("backpack.obj");

		mdl->SetShader(shd);

		ent = new StaticMeshEntity(mdl);
		ent->SetUniqueId(0);
		ent2 = new StaticMeshEntity(mdl);
		ent2->GetTransform()->Position.z = -20;
		ent2->SetUniqueId(1);
		ent3 = new StaticMeshEntity(mdl);
		ent3->GetTransform()->Position.x = -10;
		ent3->SetUniqueId(2);
		ent3->GetTransform()->EulerRotation.z = 90.0f;
		ent3->GetTransform()->Position.x = 0;

		ent4 = new StaticMeshEntity(mdl);
		ent4->GetTransform()->Position.x = 10.0f;
		ent4->SetUniqueId(3);
		ent4->GetTransform()->Position.z = 3;
		ent4->GetTransform()->Position.x = 3;

		mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
		mEngine->GetWorldSubsystem()->AddEntityToScene(ent);
	}

	void FloatingCubesGameSubsystem::ShutDown()
	{
		using namespace Oyun;
		LOG << "FloatingCubesGameSubsystem Shutdown";
		delete this;
	}

	void FloatingCubesGameSubsystem::GameLoop(float deltaTime)
	{
		GameSubsystem::GameLoop(deltaTime);
		using namespace Oyun;
		
		/*EditorDefaultCameraman->camera->Position.x = 10*sinf(angle);
		EditorDefaultCameraman->camera->Position.z = 10*cosf(angle);
		angle += deltaTime;

		ent->GetTransform()->EulerRotation.y = 180.0f * sinf(angle);
		ent3->GetTransform()->EulerRotation.z = 180.0f * sinf(angle);
		ent4->GetTransform()->EulerRotation.x = 180.0f * sinf(angle);*/
		//EditorDefaultCameraman->camera->Position.x = 10 * sinf(angle);
		//EditorDefaultCameraman->camera->Position.z = 10 * cosf(angle);
		mAngle += deltaTime;
		ent->GetTransform()->EulerRotation.y = 180.0f * sinf(mAngle);
		ent->GetTransform()->EulerRotation.y = 180.0f * sinf(mAngle);
		ent3->GetTransform()->EulerRotation.z = 180.0f * sinf(mAngle);
		ent4->GetTransform()->EulerRotation.x = 180.0f * sinf(mAngle);
		
		return;

		bool p_open = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("TEST", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::End();
	}

	void FloatingCubesGameSubsystem::SetEngine(Oyun::Engine* eng)
	{
		mEngine = eng;
	}

	
}