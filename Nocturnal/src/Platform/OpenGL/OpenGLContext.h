#pragma once
#include "Nocturnal/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Nocturnal
{
	class OpenGLContext : public RendererContext
	{
	private:
		GLFWwindow* _WindowHandle;
			
	public:
		OpenGLContext(GLFWwindow* window);
		void Init() override;
		void SwapBuffers() override;
	};
}
