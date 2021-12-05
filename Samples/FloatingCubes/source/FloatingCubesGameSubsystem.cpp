#include "FloatingCubesGameSubsystem.h"
#include <subsystems/LogSubsystem.h>
#include <subsystems/WorldSubsystem.h>
#include <EngineGlfwImguiHandler.h>
#include <CameraManager.h>
#include <Camera.h>
#include <Entity.h>
#include <subsystems/ResourceSubsystem.h>
#include <ModelStore.h>
#include <Shader.h>
#include <components/TransformComponent.h>

namespace Editor
{

	FloatingCubesGameSubsystem* FloatingCubesGameSubsystem::system = nullptr;

	FloatingCubesGameSubsystem::FloatingCubesGameSubsystem()
		:GameSubsystem()/*, EditorDefaultCameraman{ nullptr }*/
	{
		GameName = "Floating Cubes";
		GameVersion = "v0.0.0.1d";
	}

	FloatingCubesGameSubsystem::~FloatingCubesGameSubsystem()
	{
		system = nullptr;
	}

	FloatingCubesGameSubsystem* FloatingCubesGameSubsystem::GetPtr()
	{
		return system;
	}

	FloatingCubesGameSubsystem& FloatingCubesGameSubsystem::Get()
	{
		return *system;
	}

	FloatingCubesGameSubsystem& FloatingCubesGameSubsystem::Instantiate()
	{
		using namespace Oyun;
		
		//Oyun::ASSERT(system == nullptr, "FloatingCubesGameSubsystem can't initialize" );
		system = new FloatingCubesGameSubsystem();
		return *system;
	}


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aNormal;\n"
		"layout (location = 2) in vec2 aTexCoords;\n"
		"out vec2 TexCoords;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"    TexCoords = aTexCoords;    \n"
		"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"}\0";

	const char* simplefragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoords;\n"
		"uniform sampler2D texture_diffuse0;\n"
		"void main()\n"
		"{    \n"
		"    FragColor = texture(texture_diffuse0, TexCoords);\n"
		"}\0";

	Oyun::StaticMeshEntity* ent;
	Oyun::StaticMeshEntity* ent2;
	Oyun::StaticMeshEntity* ent3;
	Oyun::StaticMeshEntity* ent4;
	void FloatingCubesGameSubsystem::StartUp()
	{
		GameSubsystem::StartUp();

		using namespace Oyun;
		LOG << "FloatingCubesGameSubsystem Startup" << END;

		//EditorDefaultCameraman = Oyun::CreateCameraman(glm::vec3(0.0f, 0.0f, 10.0f));
		//EditorDefaultCameraman->isActive = true;
		//CreateUIElements();

		//Shader* shd = ResourceSubsystem::Get().LoadShader("testShader", vertexShaderSource, simplefragmentShaderSource);
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

		//WorldSubsystem::Get().AddEntityToScene(ent);
		//WorldSubsystem::Get().AddEntityToScene(ent2);
		//WorldSubsystem::Get().AddEntityToScene(ent3);
		//WorldSubsystem::Get().AddEntityToScene(ent4);
		//
	}

	void FloatingCubesGameSubsystem::ShutDown()
	{
		using namespace Oyun;
		LOG << "FloatingCubesGameSubsystem Shutdown" << END;
		delete this;
	}

	void FloatingCubesGameSubsystem::GameLoop(float deltaTime)
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

	
}