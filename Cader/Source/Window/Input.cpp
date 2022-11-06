#include "Cader/Window/Input.h"

#include "Cader/Core/Engine.h"
#include "Cader/Window/Event.h"
#include "Cader/Window/EventSystem.h"
#include "Cader/Window/Window.h"

#include <GLFW/glfw3.h>

namespace CDR {

	constexpr EKeyCode GLFW2KeyCode(int pKey) noexcept
	{
		switch(pKey)
		{
			case GLFW_KEY_A: return EKeyCode::A;
			case GLFW_KEY_B: return EKeyCode::B;
			case GLFW_KEY_C: return EKeyCode::C;
			case GLFW_KEY_D: return EKeyCode::D;
			case GLFW_KEY_E: return EKeyCode::E;
			case GLFW_KEY_F: return EKeyCode::F;
			case GLFW_KEY_G: return EKeyCode::G;
			case GLFW_KEY_H: return EKeyCode::H;
			case GLFW_KEY_I: return EKeyCode::I;
			case GLFW_KEY_J: return EKeyCode::J;
			case GLFW_KEY_K: return EKeyCode::K;
			case GLFW_KEY_L: return EKeyCode::L;
			case GLFW_KEY_M: return EKeyCode::M;
			case GLFW_KEY_N: return EKeyCode::N;
			case GLFW_KEY_O: return EKeyCode::O;
			case GLFW_KEY_P: return EKeyCode::P;
			case GLFW_KEY_Q: return EKeyCode::Q;
			case GLFW_KEY_R: return EKeyCode::R;
			case GLFW_KEY_S: return EKeyCode::S;
			case GLFW_KEY_T: return EKeyCode::T;
			case GLFW_KEY_U: return EKeyCode::U;
			case GLFW_KEY_V: return EKeyCode::V;
			case GLFW_KEY_W: return EKeyCode::W;
			case GLFW_KEY_X: return EKeyCode::X;
			case GLFW_KEY_Y: return EKeyCode::Y;
			case GLFW_KEY_Z: return EKeyCode::Z;

			case GLFW_KEY_1: return EKeyCode::_1;
			case GLFW_KEY_2: return EKeyCode::_2;
			case GLFW_KEY_3: return EKeyCode::_3;
			case GLFW_KEY_4: return EKeyCode::_4;
			case GLFW_KEY_5: return EKeyCode::_5;
			case GLFW_KEY_6: return EKeyCode::_6;
			case GLFW_KEY_7: return EKeyCode::_7;
			case GLFW_KEY_8: return EKeyCode::_8;
			case GLFW_KEY_9: return EKeyCode::_9;
			case GLFW_KEY_0: return EKeyCode::_0;

			case GLFW_KEY_KP_1: return EKeyCode::KP1;
			case GLFW_KEY_KP_2: return EKeyCode::KP2;
			case GLFW_KEY_KP_3: return EKeyCode::KP3;
			case GLFW_KEY_KP_4: return EKeyCode::KP4;
			case GLFW_KEY_KP_5: return EKeyCode::KP5;
			case GLFW_KEY_KP_6: return EKeyCode::KP6;
			case GLFW_KEY_KP_7: return EKeyCode::KP7;
			case GLFW_KEY_KP_8: return EKeyCode::KP8;
			case GLFW_KEY_KP_9: return EKeyCode::KP9;
			case GLFW_KEY_KP_0: return EKeyCode::KP0;

			case GLFW_KEY_GRAVE_ACCENT: return EKeyCode::Grave;
			case GLFW_KEY_MINUS: return EKeyCode::Minus;
			case GLFW_KEY_EQUAL: return EKeyCode::Equal;
			case GLFW_KEY_LEFT_BRACKET: return EKeyCode::LBracket;
			case GLFW_KEY_RIGHT_BRACKET: return EKeyCode::RBracket;
			case GLFW_KEY_SEMICOLON: return EKeyCode::Semicolon;
			case GLFW_KEY_APOSTROPHE: return EKeyCode::Apostrophe;
			case GLFW_KEY_COMMA: return EKeyCode::Comma;
			case GLFW_KEY_PERIOD: return EKeyCode::Period;
			case GLFW_KEY_SLASH: return EKeyCode::Slash;
			case GLFW_KEY_BACKSLASH: return EKeyCode::BackSlash;

			case GLFW_KEY_KP_DECIMAL: return EKeyCode::KPDecimal;
			case GLFW_KEY_KP_ADD: return EKeyCode::KPAdd;
			case GLFW_KEY_KP_SUBTRACT: return EKeyCode::KPSubtract;
			case GLFW_KEY_KP_MULTIPLY: return EKeyCode::KPMultiply;
			case GLFW_KEY_KP_DIVIDE: return EKeyCode::KPDivide;

			case GLFW_KEY_UP: return EKeyCode::Up;
			case GLFW_KEY_DOWN: return EKeyCode::Down;
			case GLFW_KEY_LEFT: return EKeyCode::Left;
			case GLFW_KEY_RIGHT: return EKeyCode::Right;

			case GLFW_KEY_F1: return EKeyCode::F1;
			case GLFW_KEY_F2: return EKeyCode::F2;
			case GLFW_KEY_F3: return EKeyCode::F3;
			case GLFW_KEY_F4: return EKeyCode::F4;
			case GLFW_KEY_F5: return EKeyCode::F5;
			case GLFW_KEY_F6: return EKeyCode::F6;
			case GLFW_KEY_F7: return EKeyCode::F7;
			case GLFW_KEY_F8: return EKeyCode::F8;
			case GLFW_KEY_F9: return EKeyCode::F9;
			case GLFW_KEY_F10: return EKeyCode::F10;
			case GLFW_KEY_F11: return EKeyCode::F11;
			case GLFW_KEY_F12: return EKeyCode::F12;

			case GLFW_KEY_ESCAPE: return EKeyCode::Escape;
			case GLFW_KEY_TAB: return EKeyCode::Tab;
			case GLFW_KEY_LEFT_SHIFT: return EKeyCode::LShift;
			case GLFW_KEY_RIGHT_SHIFT: return EKeyCode::RShift;
			case GLFW_KEY_LEFT_CONTROL: return EKeyCode::LCtrl;
			case GLFW_KEY_RIGHT_CONTROL: return EKeyCode::RCtrl;
			case GLFW_KEY_LEFT_ALT: return EKeyCode::LAlt;
			case GLFW_KEY_RIGHT_ALT: return EKeyCode::RAlt;
			case GLFW_KEY_SPACE: return EKeyCode::Space;
			case GLFW_KEY_BACKSPACE: return EKeyCode::BackSpace;
			case GLFW_KEY_ENTER: return EKeyCode::Enter;
			case GLFW_KEY_KP_ENTER: return EKeyCode::KPEnter;

			default: return EKeyCode::None;
		}
	}

	constexpr EMouseButton GLFW2MouseButton(int pButton)
	{
		switch(pButton)
		{
			case GLFW_MOUSE_BUTTON_LEFT: return EMouseButton::Left;
			case GLFW_MOUSE_BUTTON_RIGHT: return EMouseButton::Right;
			case GLFW_MOUSE_BUTTON_MIDDLE: return EMouseButton::Middle;

			default: return EMouseButton::None;
		}
	}

	constexpr EInputState GLFW2InputState(int pAction)
	{
		switch(pAction)
		{
			case GLFW_PRESS: return EInputState::Pressed;
			case GLFW_RELEASE: return EInputState::Released;

			default: return EInputState::None;
		}
	}

	EInputMode Input::sInputMode = EInputMode::Default;

	EInputState Input::sKeyStates[(i8)EKeyCode::Count] = {};
	EInputState Input::sMouseButtonStates[(i8)EMouseButton::Count] = {};

	MousePosition Input::sMousePosition;
	i8 Input::sMouseScroll = 0;

	Input::Input(Window* pWindow)
	{
		GLFWwindow* window = pWindow->GetNativeWindow();

		glfwSetKeyCallback(window, [](GLFWwindow* pWindow, int pKey, int pScanCode, int pAction, int pMods)
		{
			if(pAction == GLFW_REPEAT)
				return;

			const EKeyCode keyCode = GLFW2KeyCode(pKey);

			if((i8)keyCode < (i8)EKeyCode::Count && (i8)keyCode >= 0)
			{
				const EInputState state = GLFW2InputState(pAction);

				sKeyStates[(i8)keyCode] = state;

				Event e(EEventType::Key);
				e.key = {keyCode, state};
				EventSystem::FireEvent(e);
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* pWindow, int pButton, int pAction, int pMods)
		{
			if(pAction == GLFW_REPEAT)
				return;

			const EMouseButton button = GLFW2MouseButton(pButton);

			if((i8)button < (i8)EMouseButton::Count && (i8)button >= 0)
			{
				const EInputState state = GLFW2InputState(pAction);

				sMouseButtonStates[(i8)button] = state;

				Event e(EEventType::MouseButton);
				e.mouseButton = {button, state};
				EventSystem::FireEvent(e);
			}
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* pWindow, double pX, double pY)
		{
			sMousePosition = {(u16)pX, (u16)pY};

			Event e(EEventType::MousePosition);
			e.mousePosition = {(u16)pX, (u16)pY};
			EventSystem::FireEvent(e);
		});

		glfwSetScrollCallback(window, [](GLFWwindow* pWindow, double pX, double pY)
		{
			sMouseScroll = (i8)pY;

			Event e(EEventType::MouseScroll);
			e.mouseScroll = (i8)pY;
			EventSystem::FireEvent(e);
		});
	}

	// This might be very inefficient
	void Input::Update()
	{
		for(i8 i = 0; i < (i8)EKeyCode::Count; i++)
		{
			switch(sKeyStates[i])
			{
				case EInputState::Pressed:
				{
					sKeyStates[i] = EInputState::Repeated;
					break;
				}
				case EInputState::Released:
				{
					sKeyStates[i] = EInputState::None;
					break;
				}

				default: break;
			}
		}

		for(i8 i = 0; i < (i8)EMouseButton::Count; i++)
		{
			switch(sMouseButtonStates[i])
			{
				case EInputState::Pressed:
				{
					sMouseButtonStates[i] = EInputState::Repeated;
					break;
				}
				case EInputState::Released:
				{
					sMouseButtonStates[i] = EInputState::None;
					break;
				}

				default: break;
			}
		}
	}

	void Input::SetInputMode(EInputMode pInputMode)
	{
		if(sInputMode == pInputMode)
			return;

		GLFWwindow* window = Engine::Get().GetWindow()->GetNativeWindow();

		switch(pInputMode)
		{
			case CDR::EInputMode::Default:
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			}
			case CDR::EInputMode::Hidded:
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;
			}
			case CDR::EInputMode::Locked:
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
			}
			default: break;
		}

		sInputMode = pInputMode;
	}

}