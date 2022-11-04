#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/InputInfo.h"

namespace CDR {

	class Engine;
	class Window;

	class Input final
	{
		friend Engine;

		static EInputState sKeyStates[(i8)EKeyCode::Count];
		static EInputState sMouseButtonStates[(i8)EMouseButton::Count];

		static MousePosition sMousePosition;
		static i8 sMouseScroll;

		Input(Window* pWindow);
		void Update();

	public:
		static inline bool KeyDown(EKeyCode pKeyCode) noexcept { return sKeyStates[(i8)pKeyCode] == EInputState::Pressed; }
		static inline bool Key(EKeyCode pKeyCode) noexcept { return (u8)sKeyStates[(i8)pKeyCode] > (u8)EInputState::Released; }
		static inline bool KeyUp(EKeyCode pKeyCode) noexcept { return sKeyStates[(i8)pKeyCode] == EInputState::Released; }

		static inline bool MouseButtonDown(EMouseButton pButton) noexcept { return sMouseButtonStates[(i8)pButton] == EInputState::Pressed; }
		static inline bool MouseButton(EMouseButton pButton) noexcept { return (u8)sMouseButtonStates[(i8)pButton] > (u8)EInputState::Released; }
		static inline bool MouseButtonUp(EMouseButton pButton) noexcept { return sMouseButtonStates[(i8)pButton] == EInputState::Released; }

		static inline MousePosition MousePosition() noexcept { return sMousePosition; }
		static inline i8 MouseScroll() noexcept { return sMouseScroll; }
	};

}