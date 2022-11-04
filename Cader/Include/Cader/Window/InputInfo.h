#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	enum class EKeyCode: i8
	{
		None = -1,

		A, B, C, D, E, F, G,
		H, I, J, K, L, M, N,
		O, P, Q, R, S, T, U,
		V, W, X, Y, Z,

		_1, _2, _3, _4, _5,
		_6, _7, _8, _9, _0,

		KP1, KP2, KP3, KP4,
		KP5, KP6, KP7, KP8,
		KP9, KP0,

		Grave,
		Minus, Equal,
		LBracket, RBracket,
		Semicolon, Apostrophe,
		Comma, Period,
		Slash, BackSlash,

		KPDecimal,
		KPAdd, KPSubtract,
		KPMultiply, KPDivide,

		Up, Down,
		Left, Right,

		F1, F2, F3, F4,
		F5, F6, F7, F8,
		F9, F10, F11, F12,

		Escape, Tab,
		LShift, RShift,
		LCtrl, RCtrl,
		LAlt, RAlt,
		Space, BackSpace,
		Enter, KPEnter,

		Count
	};

	enum class EMouseButton: i8
	{
		None = -1,

		Left, Right, Middle,

		Count
	};

	enum class EInputState: u8
	{
		None = 0,
		Released, Pressed, Repeated
	};

	struct Key final
	{
		EKeyCode keyCode = EKeyCode::None;
		EInputState state = EInputState::None;

		constexpr Key() = default;

		constexpr Key(EKeyCode pKeyCode, EInputState pState)
			: keyCode(pKeyCode)
			, state(pState)
		{}
	};

	struct MouseButton final
	{
		EMouseButton button = EMouseButton::None;
		EInputState state = EInputState::None;

		constexpr MouseButton() = default;

		constexpr MouseButton(EMouseButton pButton, EInputState pState)
			: button(pButton)
			, state(pState)
		{}
	};

	struct MousePosition final
	{
		u16 x = 0;
		u16 y = 0;

		constexpr MousePosition() = default;

		constexpr  MousePosition(u16 pX, u16 pY)
			: x(pX)
			, y(pY)
		{}
	};

}