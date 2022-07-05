#include "atnpch.h"
#include "OpenGLGraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Athena
{
	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ATN_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLGraphicsContext::Init()
	{
		ATN_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ATN_CORE_ASSERT(status, "Failed to initialize Glad");

		ATN_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
		ATN_CORE_INFO("Graphics Card: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		ATN_PROFILE_FUNCTION();	

		glfwSwapBuffers(m_WindowHandle);
	}
}

