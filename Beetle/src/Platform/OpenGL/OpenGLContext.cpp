#include "btpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Beetle {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		BT_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		BT_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BT_CORE_ASSERT(status, "Failed to initialize Glad~!");

		BT_CORE_INFO("OpenGL vendor Info: {0} ", (const char*)glGetString(GL_VENDOR));
		BT_CORE_INFO("OpenGL renderer Info: {0} ", (const char*)glGetString(GL_RENDERER));
		BT_CORE_INFO("OpenGL version Info: {0} ", (const char*)glGetString(GL_VERSION));

		BT_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Beetle requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		BT_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}