#pragma once
#include "Nocturnal/Renderer/RendererContext.h"
#include "OpenGLShader.h"
#include "Nocturnal/Renderer/Buffer.h"
#include "Nocturnal/Renderer/VertexArray.h"

struct GLFWwindow;

namespace Nocturnal
{
	class OpenGLContext : public RendererContext
	{
	private:
		GLFWwindow* _windowHandle;
			
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}
