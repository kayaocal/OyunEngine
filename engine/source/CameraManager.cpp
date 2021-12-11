#include "CameraManager.h"
#include "Camera.h"

namespace Oyun
{
	std::vector<Cameraman*> CameramanList;

	Cameraman::Cameraman(glm::vec3 pos, Window* w)
		:camera(new Camera(pos)),wnd(w), isActive(false)
	{
	}

	Cameraman::~Cameraman()
	{
		delete camera;
	}

	Cameraman* CreateCameraman(glm::vec3& pos, Window* w)
	{
		assert(CameramanList.size() < 14);
		Cameraman* cam = new Cameraman(pos, w);
		CameramanList.push_back(cam);
		return cam;
	}

	void DeleteAllCameramans(Window* wnd)
	{
		

		auto iterator = std::remove_if(CameramanList.begin(), CameramanList.end(), [&](Cameraman* cam)
			{
				
				if (cam->wnd == wnd)
				{
					delete cam;
					return true;
				}
				return false;
			});

		CameramanList.erase(iterator, CameramanList.end());

	}



}