#pragma once

#define EngineExport  __declspec( dllexport )

namespace Oyun
{
	EngineExport extern const char* EngineName;
	EngineExport extern const char* Engine;
	EngineExport extern const char* EngineDescription;
	
	EngineExport extern unsigned long gFrameCount;
	EngineExport extern float gDeltaTime;
	EngineExport extern float glastRenderTime;

	EngineExport void StartEngine();
	EngineExport void ShutdownEngine();
	EngineExport void Loop();
	EngineExport void OnEngineStarted();
}