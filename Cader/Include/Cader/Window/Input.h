#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/InputInfo.h"

namespace CDR {

	class Engine;
	class Window;

	class Input final
	{
		friend Engine;

		static EInputMode sInputMode;

		static EInputState sKeyStates[(i8)EKeyCode::Count];
		static EInputState sMouseButtonStates[(i8)EMouseButton::Count];

		static MousePosition sMousePosition;
		static i8 sMouseScroll;

		Input(Window* pWindow);
		void Update();

	public:
		static void SetInputMode(EInputMode pInputMode);
		static inline EInputMode GetInputMode() noexcept { return sInputMode; }

		static inline bool GetKeyDown(EKeyCode pKeyCode) noexcept { return sKeyStates[(i8)pKeyCode] == EInputState::Pressed; }
		static inline bool GetKey(EKeyCode pKeyCode) noexcept { return (u8)sKeyStates[(i8)pKeyCode] > (u8)EInputState::Released; }
		static inline bool GetKeyUp(EKeyCode pKeyCode) noexcept { return sKeyStates[(i8)pKeyCode] == EInputState::Released; }

		static inline bool GetMouseButtonDown(EMouseButton pButton) noexcept { return sMouseButtonStates[(i8)pButton] == EInputState::Pressed; }
		static inline bool GetMouseButton(EMouseButton pButton) noexcept { return (u8)sMouseButtonStates[(i8)pButton] > (u8)EInputState::Released; }
		static inline bool GetMouseButtonUp(EMouseButton pButton) noexcept { return sMouseButtonStates[(i8)pButton] == EInputState::Released; }

		static inline MousePosition GetMousePosition() noexcept { return sMousePosition; }
		static inline i8 GetMouseScroll() noexcept { return sMouseScroll; }
	};

}