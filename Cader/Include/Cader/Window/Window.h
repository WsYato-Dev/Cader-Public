#pragma once

#include "Cader/Core/PersistentSettings.h"
#include "Cader/Core/StartupSettings.h"
#include "Cader/Types/Common.h"
#include "Cader/Window/WindowSettings.h"

struct GLFWwindow;

namespace CDR {

	class Engine;

	class Window final
	{
		Window(const PersistentSettings& pPersistentSettings, const StartupSettings& pStartupSettings);
		~Window();

		void SetCallbacks();
		void OnResize();

		void PollEvents();
		void WaitEvents();

	public:
		void SetTitle(Text pTitle);
		void SetSize(WindowSize pSize);
		void SetMode(EWindowMode pMode);

		Text GetTitle() const noexcept { return mTitle; }
		WindowSize GetSize() const noexcept { return mSize; }
		EWindowMode GetMode() const noexcept { return mMode; }

		GLFWwindow* GetNativeWindow() const noexcept { return mWindow; }

		bool IsFocused() const noexcept { return mFocused; }

	private:
		GLFWwindow* mWindow;

		Text mTitle;

		WindowSize mSize;
		WindowSize mLateSize;

		EWindowMode mMode;

		bool mMinimized{false};
		bool mFocused{true};
		bool mResized{false};

		friend Engine;
	};

}