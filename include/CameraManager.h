#pragma once
#include <vector>
#include <glm/glm.hpp>

#define EngineExport  __declspec( dllexport )
namespace Oyun
{
	class Camera;

	struct EngineExport Cameraman
	{
		Cameraman() = delete;

		Cameraman(glm::vec3 pos);
		~Cameraman();

		Camera* camera;
		bool isActive;

	};


	EngineExport extern std::vector<Cameraman*> CameramanList;

	EngineExport Cameraman* CreateCameraman(glm::vec3& pos);
	EngineExport void DeleteAllCameramans();

	

}