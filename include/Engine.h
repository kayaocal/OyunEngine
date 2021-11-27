#pragma once

#define EngineExport  __declspec( dllexport )

namespace Oyun
{
	EngineExport extern const char* EngineName;
	EngineExport extern const char* EngineVersion;
	EngineExport extern const char* EngineDescription;
	
	/// @brief Frame count since game started
	EngineExport extern unsigned long gFrameCount;

	/// @brief time of last frame. (seconds)
	EngineExport extern double gDeltaTime;
	
	/// @brief time spent to render scene (seconds)
	EngineExport extern double glastRenderTime;
	
	/// @brief 1.0f / gDeltaTime
	EngineExport extern double gInstantFps;
	/// @brief Frame count in last seconds
	EngineExport extern int gFps;

	class GameSubsystem;
	
	/// @brief Initializes and starts engine and it's all subsystems.
	/// After initialization process it starts main loop.
	/// @param Pointer of class derrived from GameSubsystem
	EngineExport void StartEngine(GameSubsystem* game);
	
	/// @brief Closes engine and game
	EngineExport void ShutdownEngine();


	EngineExport void Loop(GameSubsystem* game);




}



