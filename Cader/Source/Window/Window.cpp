#include "Cader/Window/Window.h"

#include "Cader/Utility/Assert.h"
#include "Cader/Window/Event.h"
#include "Cader/Window/EventSystem.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace CDR {

	Window::Window(Text pTitle, const StartupSettings& pStartupSettings)
		: mTitle{pTitle}
		, mMode{pStartupSettings.windowMode}
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_VISIBLE, false);
		glfwWindowHint(GLFW_RESIZABLE, pStartupSettings.windowResizable);

		if(pStartupSettings.windowDefaultSize.width > 0 && pStartupSettings.windowDefaultSize.height > 0)
			mSize = pStartupSettings.windowDefaultSize;
		else
			mSize = {1280, 720};

		mSizeBeforeFullscreen = mSize;

		switch(pStartupSettings.windowMode)
		{
			case EWindowMode::Windowed:
			{
				mWindow = glfwCreateWindow(mSize.width, mSize.height, pTitle, nullptr, nullptr);
				break;
			}
			case EWindowMode::Maximized:
			{
				glfwWindowHint(GLFW_MAXIMIZED, true);
				mWindow = glfwCreateWindow(mSize.width, mSize.height, pTitle, nullptr, nullptr);
				break;
			}
			case EWindowMode::Fullscreen:
			{
				GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
				mWindow = glfwCreateWindow(videoMode->width, videoMode->height, pTitle, primaryMonitor, nullptr);
				break;
			}
		}

		CDR_ASSERT(mWindow);

		glfwSetWindowUserPointer(mWindow, this);

		if(pStartupSettings.windowMinimumSize.width > 0 || pStartupSettings.windowMinimumSize.height > 0)
			glfwSetWindowSizeLimits(mWindow, pStartupSettings.windowMinimumSize.width, pStartupSettings.windowMinimumSize.height, GLFW_DONT_CARE, GLFW_DONT_CARE);

		if(pStartupSettings.windowAspectRatio.numerator > 0 && pStartupSettings.windowAspectRatio.denominator > 0)
			glfwSetWindowAspectRatio(mWindow, pStartupSettings.windowAspectRatio.numerator, pStartupSettings.windowAspectRatio.denominator);

		SetCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::SetCallbacks()
	{
		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* pWindow)
		{
			Event e(EEventType::WindowClose);
			EventSystem::FireEvent(e, true);
		});

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* pWindow, int pWidth, int pHeight)
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
		});

		glfwSetWindowFocusCallback(mWindow, [](GLFWwindow* pWindow, int pFocused)
		{
			Window& user = *(Window*)glfwGetWindowUserPointer(pWindow);

			user.mFocused = pFocused;

			Event e(EEventType::WindowFocus);
			e.windowFocused = pFocused;
			EventSystem::FireEvent(e);
		});
	}

	void Window::OnResize()
	{
		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);

		mSize.width = (u16)width;
		mSize.height = (u16)height;

		Event e(EEventType::WindowResize);
		e.windowSize = {mSize.width, mSize.height};
		EventSystem::FireEvent(e);

		mResized = false;
	}

	void Window::Show()
	{
		glfwShowWindow(mWindow);
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

	void Window::SetTitle(Text pTitle)
	{
		if(mTitle == pTitle)
			return;

		glfwSetWindowTitle(mWindow, pTitle);
		mTitle = pTitle;
	}

	void Window::SetSize(WindowSize pSize)
	{
		if(mSize == pSize || mMode != EWindowMode::Windowed)
			return;

		glfwSetWindowSize(mWindow, pSize.width, pSize.height);
		mSize = pSize;
	}

	void Window::SetMode(EWindowMode pMode)
	{
		if(mMode == pMode)
			return;

		if(mMode == EWindowMode::Fullscreen)
			glfwSetWindowMonitor(mWindow, nullptr, 100, 100, mSizeBeforeFullscreen.width, mSizeBeforeFullscreen.height, GLFW_DONT_CARE);

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
				mSizeBeforeFullscreen = mSize;

				GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
				glfwSetWindowMonitor(mWindow, primaryMonitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
				break;
			}
		}

		mMode = pMode;
	}

}