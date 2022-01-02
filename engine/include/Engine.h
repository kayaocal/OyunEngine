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
	OYUN_API extern int gFrameCount;
	
	class GameSubsystem;
	class RenderSubsystem;
	class WorldSubsystem;
	class InputSubsystem;
	struct Window;

	struct OYUN_API Engine
	{
		/// @brief Frame count since game started
		unsigned long frameCount;

		/// @brief time of last frame. (seconds)
		float deltaTime;
	
		/// @brief time spent to render scene (seconds)
		double lastRenderTime;
	
		/// @brief 1.0f / mDeltaTime
		double instantFps;
		/// @brief Frame count in last seconds
		int fps;

		bool engineRunning;
		
		Engine(GameSubsystem* game, RenderSubsystem* renderer, WorldSubsystem* world, Window* shared = nullptr);
		~Engine();

		GameSubsystem* GetGameSubsystem() const;
		RenderSubsystem* GetRenderSubsystem() const;
		WorldSubsystem* GetWorldSubsystem() const;
		InputSubsystem* GetInputSubsystem() const;
		
		template <class T>
		T* GetGameSubsystem() const
		{
			return dynamic_cast<T*>(mGameSubsystem);
		}
		
		void StartUp();

		void ShutDown();

		void Loop();

		void Close();
		
		private:
		
		GameSubsystem* mGameSubsystem;
		RenderSubsystem* mRenderSubsystem;
		WorldSubsystem* mWorldSubsystem;
		InputSubsystem* mInputSubsystem;

		double mFpsTimer = 0;
		int mFpsSum = 0;
		
	};

}



#endif //OYUN_ENGINE_H__