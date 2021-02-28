#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"
#include "Nocturnal/Application.h"

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

		//glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLContext::SwapBuffers()
	{
		
		
		glfwSwapBuffers(_WindowHandle);

		//float width = Application::Get().GetWindow().GetWidth();
		//float height = Application::Get().GetWindow().GetHeight();
		////glViewport(0, 0, , Application::Get().GetWindow().GetHeight());
		//glViewport(0, 0, width, height);
		//glMatrixMode(GL_PROJECTION);
		//float aspect = (float)width / (float)height;
		//glOrtho(-aspect, aspect, -1, 1, -1, 1);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
	}

	
}
