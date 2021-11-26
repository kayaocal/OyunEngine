#include "CameraManager.h"
#include "Camera.h"

namespace Oyun
{
	std::vector<Cameraman*> CameramanList;


	Cameraman* CreateCameraman(glm::vec3& pos)
	{
		assert(CameramanList.size() < 14);
		Cameraman* cam = new Cameraman(pos);
		CameramanList.push_back(cam);
		return cam;
	}

	void DeleteAllCameramans()
	{
		for (auto cam : CameramanList)
		{
			delete cam;
		}
	}

	Cameraman::Cameraman(glm::vec3& pos)
	{
		camera = new Camera(pos);
		isActive = true;
	}

	Cameraman::~Cameraman()
	{
		delete camera;
	}

}