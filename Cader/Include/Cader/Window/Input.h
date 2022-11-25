#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/InputInfo.h"

namespace CDR {

	class Engine;
	class Window;

	class Input final
	{
		static void Init(const Window& pWindow);
		static void Update();

	public:
		static void SetInputMode(const EInputMode pInputMode);
		static EInputMode GetInputMode() noexcept { return sInputMode; }

		static bool GetKey(const EKeyCode pKeyCode) noexcept { return (u8)EInputState::Released < (u8)sKeyStates[(i8)pKeyCode]; }
		static bool GetKeyDown(const EKeyCode pKeyCode) noexcept { return EInputState::Pressed == sKeyStates[(i8)pKeyCode]; }
		static bool GetKeyUp(const EKeyCode pKeyCode) noexcept { return EInputState::Released == sKeyStates[(i8)pKeyCode]; }

		static bool GetMouseButton(const EMouseButton pButton) noexcept { return (u8)EInputState::Released < (u8)sMouseButtonStates[(i8)pButton]; }
		static bool GetMouseButtonDown(const EMouseButton pButton) noexcept { return EInputState::Pressed == sMouseButtonStates[(i8)pButton]; }
		static bool GetMouseButtonUp(const EMouseButton pButton) noexcept { return EInputState::Released == sMouseButtonStates[(i8)pButton]; }

		static MousePosition GetMousePosition() noexcept { return sMousePosition; }
		static i8 GetMouseScroll() noexcept { return sMouseScroll; }

	private:
		static EInputMode sInputMode;

		static EInputState sKeyStates[(i8)EKeyCode::Count];
		static EInputState sMouseButtonStates[(i8)EMouseButton::Count];

		static MousePosition sMousePosition;
		static i8 sMouseScroll;

		friend Engine;
	};

}