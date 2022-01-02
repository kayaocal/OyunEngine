#include "Subsystems/InputSubsystem.h"
#include <cassert>
#include "Engine.h"

namespace Oyun
{
	
	InputSubsystem::InputSubsystem()
		:EngineSubsytem()
	{
	}

	InputSubsystem::~InputSubsystem()
	{
	}


	void InputSubsystem::StartUp()
	{
	}
	
	void InputSubsystem::ShutDown()
	{
	}

	void InputSubsystem::SetEngine(Engine* engine)
	{
		mEngine = engine;
	}

	bool InputSubsystem::IsKeyDown(KeyCode key)
	{
		return mKeys[static_cast<int>(key)].state == KeyState::PRESSED;
	}


	void InputSubsystem::UpdateKeyStatus(KeyCode key, KeyState state)
	{
		if (key == KeyCode::COUNT)
		{
			return;
		}
		int keyIndex = static_cast<int>(key);
		assert(keyIndex >= 0 && keyIndex < static_cast<int>(KeyCode::COUNT));

		KeyState prevState = mKeys[keyIndex].state;
		if (prevState != state)
		{
			mKeys[keyIndex].state = state;
			auto time = std::chrono::high_resolution_clock::now();
			
			if (state == KeyState::RELEASED)
			{
				//Notify listeners

			}
			else if (state == KeyState::PRESSED)
			{
				//Notify listeners
			}
			mKeys[keyIndex].lastKeyStateChangeTime =  time;
		}
	}

	void InputSubsystem::SetMousePos(float x, float y)
	{
		mMousePos.Set(x, y);
	}

	const Vec2& InputSubsystem::GetMousePos()
	{
		return mMousePos;
	}

	void InputSubsystem::SetMouseScroll(float x, float y)
	{
		mMouseScroll.Set(x, y);
	}

	const Vec2& InputSubsystem::GetMouseScroll()
	{
		return mMouseScroll;
	}
}
