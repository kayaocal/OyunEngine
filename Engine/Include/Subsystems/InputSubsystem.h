#ifndef INPUT_SUBSYSTEM__
#define INPUT_SUBSYSTEM__

#include "EngineSubsytem.h"
#include <chrono>

#include "Math/Vector.h"

namespace Oyun
{
	class Engine;
	/// @brief There might be missing keys here
	enum class KeyCode
	{
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_MIDDLE,
		MOUSE_4,
		MOUSE_5,
		MOUSE_6,
		MOUSE_7,
		KEY_SPACE,
		KEY_APOSTROPHE,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON,
		KEY_EQUAL,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_BRACKET_L,
		KEY_BACK_SLASH,
		KEY_BRACKET_R,
		KEY_ACCENT,
		KEY_ESCAPE,
		KEY_ENTER,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_INSERT,
		KEY_DELETE,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_CAPSLOCK,
		KEY_SCROLL_LOCK,
		KEY_NUMLOCK,
		KEY_PRINT_SCREEN,
		KEY_PAUSE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_F16,
		KEY_F17,
		KEY_F18,
		KEY_F19,
		KEY_F20,
		KEY_F21,
		KEY_F22,
		KEY_F23,
		KEY_F24,
		KEY_F25,
		NUM_0,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		NUM_FWD_SLASH,
		NUM_ASTERISK,
		NUM_MINUS,
		NUM_PLUS,
		NUM_ENTER,
		KEY_SHIFT_L,
		KEY_CTRL_L,
		KEY_ALT_R,
		KEY_WINDOW_L,
		KEY_SHIFT_R,
		KEY_CTRL_R,
		KEY_ALT_L,
		KEY_WINDOW_R,
		COUNT
	};

	enum class KeyState
	{
		RELEASED = 0,
		PRESSED = 1,
		UNDEFINED
	};

	struct OYUN_API KeyInfo
	{
		KeyState state;
		/// @brief used to detect key clicks
		std::chrono::steady_clock::time_point lastKeyStateChangeTime;
	};



	class OYUN_API InputSubsystem : public EngineSubsytem<InputSubsystem >
	{
		KeyInfo mKeys[static_cast<int>(KeyCode::COUNT)];
		Vec2 mMousePos;
		Vec2 mMouseScroll;
		Engine* mEngine;
		
	public:

		InputSubsystem();
		~InputSubsystem();
		
		virtual void StartUp() override;
		virtual void ShutDown() override;
		void SetEngine(Engine* engine);


		void UpdateKeyStatus(KeyCode key, KeyState state);

		void SetMousePos(float x, float y);
		const Vec2& GetMousePos();

		void SetMouseScroll(float x, float y);
		const Vec2& GetMouseScroll();

		bool IsKeyDown(KeyCode key);
		
	};
}

#endif //INPUT_SUBSYSTEM__