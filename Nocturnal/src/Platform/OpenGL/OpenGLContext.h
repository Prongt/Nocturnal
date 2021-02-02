#pragma once
#include "Nocturnal/Renderer/RendererContext.h"
#include "OpenGLShader.h"

struct GLFWwindow;

namespace Nocturnal
{
	class OpenGLContext : public RendererContext
	{
	private:
		GLFWwindow* WindowHandle;

		unsigned int VertexArrayObjectId;
		const std::string VertexShaderSource = R"(#version 330 core
			layout (location = 0) in vec3 aPos;
			out vec3 v_position;
			void main()
			{
				v_position = aPos;
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
			)";

		const std::string FragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;

			in vec3 v_position;
			void main()
			{
			   FragColor = vec4(v_position * 0.5 + 0.5, 1.0f);
			}
			)";
			

		std::unique_ptr<OpenGLShader> Shader;
			
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}
