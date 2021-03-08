#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"
#include "Nocturnal/Application.h"

namespace Nocturnal
{	
	OpenGLContext::OpenGLContext(struct  GLFWwindow* window)
		:mWindowHandle(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(mWindowHandle);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		NOC_CORE_ASSERT(status, "Failed to initialize GLAD");

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(mWindowHandle);
	}

	
}
