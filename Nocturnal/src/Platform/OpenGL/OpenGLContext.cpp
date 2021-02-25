#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"

namespace Nocturnal
{	
	OpenGLContext::OpenGLContext(struct  GLFWwindow* window)
		:_windowHandle(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(_windowHandle);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		NOC_CORE_ASSERT(status, "Failed to initialize GLAD");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}

	
}
