#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Nocturnal
{
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		//TODO originaly used draw elements
		//glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	float OpenGLRendererAPI::GetTime()
	{
		return glfwGetTime();
	}
}
