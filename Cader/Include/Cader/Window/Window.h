#pragma once

#include "Cader/Core/StartupSettings.h"
#include "Cader/Types/Common.h"
#include "Cader/Window/WindowSettings.h"

struct GLFWwindow;

namespace CDR {

	class Engine;

	class Window final
	{
		friend Engine;

		GLFWwindow* mWindow;

		Text mTitle;
		EWindowMode mMode;

		WindowSize mSize;
		WindowSize mLateSize;

		bool mMinimized{false};
		bool mFocused{true};
		bool mResized{false};

		Window(Text pTitle, const StartupSettings& pStartupSettings);
		~Window();

		void SetCallbacks();
		void OnResize();

		void Show();

		void PollEvents();
		void WaitEvents();

	public:
		void SetTitle(Text pTitle);
		void SetSize(WindowSize pSize);
		void SetMode(EWindowMode pMode);

		inline Text GetTitle() const noexcept { return mTitle; }
		inline WindowSize GetSize() const noexcept { return mSize; }
		inline EWindowMode GetMode() const noexcept { return mMode; }

		inline GLFWwindow* GetNativeWindow() const noexcept { return mWindow; }

		inline bool IsFocused() const noexcept { return mFocused; }
	};

}