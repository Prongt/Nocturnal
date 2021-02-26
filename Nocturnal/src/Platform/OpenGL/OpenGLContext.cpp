#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"

namespace Nocturnal
{	
	OpenGLContext::OpenGLContext(struct  GLFWwindow* window)
		:_WindowHandle(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(_WindowHandle);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		NOC_CORE_ASSERT(status, "Failed to initialize GLAD");

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_WindowHandle);
	}

	
}
