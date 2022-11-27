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

		static bool GetKey(const EKeyCode pKeyCode) noexcept { return  (u8)sKeyStates[(i8)pKeyCode] > (u8)EInputState::Released; }
		static bool GetKeyDown(const EKeyCode pKeyCode) noexcept { return sKeyStates[(i8)pKeyCode] == EInputState::Pressed; }
		static bool GetKeyUp(const EKeyCode pKeyCode) noexcept { return sKeyStates[(i8)pKeyCode] == EInputState::Released; }

		static bool GetMouseButton(const EMouseButton pButton) noexcept { return (u8)sMouseButtonStates[(i8)pButton] > (u8)EInputState::Released; }
		static bool GetMouseButtonDown(const EMouseButton pButton) noexcept { return sMouseButtonStates[(i8)pButton] == EInputState::Pressed; }
		static bool GetMouseButtonUp(const EMouseButton pButton) noexcept { return sMouseButtonStates[(i8)pButton] == EInputState::Released; }

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