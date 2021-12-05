#ifndef OYUN_ENGINE_H__
#define OYUN_ENGINE_H__

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	OYUN_API extern const char* EngineName;
	OYUN_API extern const char* EngineVersion;
	OYUN_API extern const char* EngineDescription;
	
	/// @brief Frame count since game started
	OYUN_API extern unsigned long gFrameCount;

	/// @brief time of last frame. (seconds)
	OYUN_API extern float gDeltaTime;
	
	/// @brief time spent to render scene (seconds)
	OYUN_API extern double glastRenderTime;
	
	/// @brief 1.0f / gDeltaTime
	OYUN_API extern double gInstantFps;
	/// @brief Frame count in last seconds
	OYUN_API extern int gFps;

	class GameSubsystem;
	
	/// @brief Initializes and starts engine and it's all subsystems.
	/// After initialization process it starts main loop.
	/// @param Pointer of class derrived from GameSubsystem
	OYUN_API void StartEngine(GameSubsystem* game);
	
	/// @brief Closes engine and game
	OYUN_API void ShutdownEngine();


	OYUN_API void Loop(GameSubsystem* game);




}



#endif //OYUN_ENGINE_H__