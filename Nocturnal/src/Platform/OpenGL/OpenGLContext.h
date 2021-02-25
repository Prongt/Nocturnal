#pragma once
#include "Nocturnal/Renderer/RendererContext.h"
#include "OpenGLShader.h"
#include "Nocturnal/Renderer/Buffer.h"

struct GLFWwindow;

namespace Nocturnal
{
	class OpenGLContext : public RendererContext
	{
	private:
		GLFWwindow* WindowHandle;

		unsigned int VertexArrayObjectId;
		const std::string VertexShaderSource = R"(#version 330 core
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;
		
			out vec3 v_position;
			out vec4 v_Color;
		
			void main()
			{
				v_Color = a_Color;
				v_position = a_Position;
				gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
			}
			)";

		const std::string FragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;

			in vec3 v_position;
			in vec4 v_Color;
		
			void main()
			{
				FragColor = vec4(v_position * 0.5 + 0.5, 1.0f);
				FragColor = v_Color;
			}
			)";
			

		std::unique_ptr<OpenGLShader> Shader;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<IndexBuffer> indexBuffer;
			
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}
