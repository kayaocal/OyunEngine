#pragma once
#include <subsystems\GameSubsystem.h>
#include "ImLayer.h"

#ifdef FloatingCubes_EXPORTS
#define FLOATINGCUBES_API __declspec(dllexport)
#else
#define FLOATINGCUBES_API __declspec(dllimport)
#endif

namespace Oyun
{
	struct Cameraman;
	struct Engine;
	class StaticMeshEntity;
}


namespace Cubes
{
	class FLOATINGCUBES_API FloatingCubesGameSubsystem : public Oyun::GameSubsystem
	{
	public:
		FloatingCubesGameSubsystem();
		virtual ~FloatingCubesGameSubsystem();


		virtual void StartUp() override;
		virtual void ShutDown() override;

		void GameLoop(float deltaTime);
		void SetEngine(Oyun::Engine*);

	private:
		float mAngle;
		Oyun::StaticMeshEntity* ent;
		Oyun::StaticMeshEntity* ent2;
		Oyun::StaticMeshEntity* ent3;
		Oyun::StaticMeshEntity* ent4;


	};
}