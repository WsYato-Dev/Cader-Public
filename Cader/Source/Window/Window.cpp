#include "Cader/Window/Window.h"

#include "Cader/Window/Event.h"

#include <assert.h>

#include <GLFW/glfw3.h>

namespace CDR {

	Window::Window(EventSystem& pEventSystem, Text pTitle, const StartupSettings& pStartupSettings)
		: mEventSystem(pEventSystem)
		, mTitle(pTitle)
		, mMode(pStartupSettings.windowMode)
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_VISIBLE, false);
		glfwWindowHint(GLFW_RESIZABLE, pStartupSettings.windowResizable);

		if(pStartupSettings.windowDefaultSize.width > 0 && pStartupSettings.windowDefaultSize.height > 0)
			mSize = pStartupSettings.windowDefaultSize;
		else
			mSize = {1280, 720};

		switch(mMode)
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

		assert(mWindow);

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
			const Window& user = *(Window*)glfwGetWindowUserPointer(pWindow);

			Event e(EEventType::WindowClose);
			user.mEventSystem.FireEvent(e, true);
		});

		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* pWindow, int pWidth, int pHeight)
		{
			Window& user = *(Window*)glfwGetWindowUserPointer(pWindow);

			if(pWidth == 0 || pHeight == 0)
			{
				user.mMinimized = true;

				Event e(EEventType::WindowMinimize);
				e.minimized = true;
				user.mEventSystem.FireEvent(e);
			}
			else if(user.mMinimized)
			{
				user.mMinimized = false;

				Event e(EEventType::WindowMinimize);
				e.minimized = false;
				user.mEventSystem.FireEvent(e);
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
			e.focused = pFocused;
			user.mEventSystem.FireEvent(e);
		});
	}

	void Window::OnResize()
	{
		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);

		mSize.width = (u16)width;
		mSize.height = (u16)height;

		Event e(EEventType::WindowResize);
		e.size.width = mSize.width;
		e.size.height = mSize.height;
		mEventSystem.FireEvent(e);
		
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

		mTitle = pTitle;
		glfwSetWindowTitle(mWindow, pTitle);
	}

	void Window::SetSize(WindowSize pSize)
	{
		if(mSize == pSize || mMode != EWindowMode::Windowed)
			return;

		mSize = pSize;
		glfwSetWindowSize(mWindow, pSize.width, pSize.height);
	}

	void Window::SetMode(EWindowMode pMode)
	{
		if(mMode == pMode)
			return;

		if(mMode == EWindowMode::Fullscreen)
			glfwSetWindowMonitor(mWindow, nullptr, 100, 100, mSize.width, mSize.height, GLFW_DONT_CARE);

		mMode = pMode;

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
				GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
				glfwSetWindowMonitor(mWindow, primaryMonitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
				break;
			}
		}
	}

}