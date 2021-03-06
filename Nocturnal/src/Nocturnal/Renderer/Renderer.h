#pragma once
#include "Camera.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "glm/glm.hpp"

namespace Nocturnal
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ModelMatrix = glm::mat4(1.0f);
			glm::mat4 ViewMatrix = glm::mat4(1.0f);
			glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
		};
		static SceneData* sSceneData;
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transformMatrix = glm::mat4(1.0f));
		static void SubmitProjectionMatrix(glm::mat4& projectionMatrix) { sSceneData->ProjectionMatrix = projectionMatrix; }
		
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	
	};
	
}
