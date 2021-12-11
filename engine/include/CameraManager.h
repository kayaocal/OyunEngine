#ifndef OYUN_CAMERA_MANAGER_H__
#define OYUN_CAMERA_MANAGER_H__

#include <vector>
#include <glm/glm.hpp>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	class Camera;
	struct Window;

	struct OYUN_API Cameraman
	{
		Cameraman() = delete;

		Cameraman(glm::vec3 pos, Window* w);
		~Cameraman();


		Camera* camera;
		Window* wnd;
		bool isActive;

	};


	OYUN_API extern std::vector<Cameraman*> CameramanList;

	OYUN_API Cameraman* CreateCameraman(glm::vec3& pos, Window* w);
	OYUN_API void DeleteAllCameramans(Window* wnd);

	

}

#endif//OYUN_CAMERA_MANAGER_H__