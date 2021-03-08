#pragma once
#include "Nocturnal/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Nocturnal
{
	class OpenGLContext : public RendererContext
	{
	private:
		GLFWwindow* mWindowHandle;
			
	public:
		OpenGLContext(GLFWwindow* window);
		void Init() override;
		void SwapBuffers() override;
	};
}
