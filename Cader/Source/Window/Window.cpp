#include "Cader/Window/Window.h"

#include "Cader/Utility/Assert.h"
#include "Cader/Window/Event.h"
#include "Cader/Window/EventSystem.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace CDR {

	Window::Window(const PersistentSettings& pPersistentSettings, const StartupSettings& pStartupSettings)
		: mTitle{pPersistentSettings.projectTitle}
		, mMode{pStartupSettings.windowMode}
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, pPersistentSettings.windowResizable);

		if(pStartupSettings.windowDefaultSize.width > 0 && pStartupSettings.windowDefaultSize.height > 0)
			mLateSize = pStartupSettings.windowDefaultSize;
		else
			mLateSize = WindowSize(1280, 720);

		switch(pStartupSettings.windowMode)
		{
			case EWindowMode::Windowed:
			{
				mWindow = glfwCreateWindow(mLateSize.width, mLateSize.height, mTitle, nullptr, nullptr);
				break;
			}
			case EWindowMode::Maximized:
			{
				glfwWindowHint(GLFW_MAXIMIZED, true);
				mWindow = glfwCreateWindow(mLateSize.width, mLateSize.height, mTitle, nullptr, nullptr);
				break;
			}
			case EWindowMode::Fullscreen:
			{
				GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
				mWindow = glfwCreateWindow(videoMode->width, videoMode->height, mTitle, primaryMonitor, nullptr);
				break;
			}
		}

		CDR_ASSERT(mWindow);

		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);
		mSize = WindowSize((u16)width, (u16)height);

		glfwSetWindowUserPointer(mWindow, this);

		if(pPersistentSettings.windowMinimumSize.width > 0 || pPersistentSettings.windowMinimumSize.height > 0)
			glfwSetWindowSizeLimits(mWindow, pPersistentSettings.windowMinimumSize.width, pPersistentSettings.windowMinimumSize.height, GLFW_DONT_CARE, GLFW_DONT_CARE);

		if(pPersistentSettings.windowAspectRatio.numerator > 0 && pPersistentSettings.windowAspectRatio.denominator > 0)
			glfwSetWindowAspectRatio(mWindow, pPersistentSettings.windowAspectRatio.numerator, pPersistentSettings.windowAspectRatio.denominator);

		SetCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::SetCallbacks()
	{
		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* pWindow) -> void {
			{
				Event e(EEventType::WindowClose);
				EventSystem::FireEvent(e, true);
			}
		});

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* pWindow, int pWidth, int pHeight) -> void {
			{
				Window& user = *(Window*)glfwGetWindowUserPointer(pWindow);

				if(pWidth == 0 || pHeight == 0)
				{
					user.mMinimized = true;

					Event e(EEventType::WindowMinimize);
					e.windowMinimized = true;
					EventSystem::FireEvent(e);
				}
				else if(user.mMinimized)
				{
					user.mMinimized = false;

					Event e(EEventType::WindowMinimize);
					e.windowMinimized = false;
					EventSystem::FireEvent(e);
				}
				else
				{
					user.mResized = true;
				}
			}
		});

		glfwSetWindowFocusCallback(mWindow, [](GLFWwindow* pWindow, int pFocused) -> void {
			{
				Window& user = *(Window*)glfwGetWindowUserPointer(pWindow);

				user.mFocused = pFocused;

				Event e(EEventType::WindowFocus);
				e.windowFocused = pFocused;
				EventSystem::FireEvent(e);
			}
		});
	}

	void Window::OnResize()
	{
		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);
		mSize = WindowSize((u16)width, (u16)height);

		Event e(EEventType::WindowResize);
		e.windowSize = {mSize.width, mSize.height};
		EventSystem::FireEvent(e);

		mResized = false;
	}

	void Window::PollEvents()
	{
		glfwPollEvents();

		if(mResized)
			OnResize();
	}

	void Window::WaitEvents()
	{
		glfwWaitEvents();

		if(mResized)
			OnResize();
	}

	void Window::SetTitle(const Text pTitle)
	{
		if(pTitle == mTitle)
			return;

		glfwSetWindowTitle(mWindow, pTitle);
		mTitle = pTitle;
	}

	void Window::SetSize(const WindowSize pSize)
	{
		if(pSize == mSize || mMode != EWindowMode::Windowed)
			return;

		glfwSetWindowSize(mWindow, pSize.width, pSize.height);
		mSize = pSize;
	}

	void Window::SetMode(const EWindowMode pMode)
	{
		if(pMode == mMode)
			return;

		if(mMode == EWindowMode::Fullscreen)
			glfwSetWindowMonitor(mWindow, nullptr, 100, 100, mLateSize.width, mLateSize.height, GLFW_DONT_CARE);

		switch(pMode)
		{
			case CDR::EWindowMode::Windowed:
			{
				glfwRestoreWindow(mWindow);
				break;
			}
			case CDR::EWindowMode::Maximized:
			{
				glfwMaximizeWindow(mWindow);
				break;
			}
			case CDR::EWindowMode::Fullscreen:
			{
				mLateSize = mSize;

				GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
				glfwSetWindowMonitor(mWindow, primaryMonitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
				break;
			}
		}

		mMode = pMode;
	}

}