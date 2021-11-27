#pragma once

#define EngineExport  __declspec( dllexport )

namespace Oyun
{
	EngineExport extern const char* EngineName;
	EngineExport extern const char* Engine;
	EngineExport extern const char* EngineDescription;
	
	EngineExport extern unsigned long gFrameCount;
	EngineExport extern double gDeltaTime;
	EngineExport extern double glastRenderTime;
	EngineExport extern double gInstantFps;
	EngineExport extern int gFps;

	class GameSubsystem;
	EngineExport void StartEngine(GameSubsystem* game);
	EngineExport void ShutdownEngine();
	EngineExport void Loop(GameSubsystem* game);




}



