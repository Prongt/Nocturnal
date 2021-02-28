#include "NocturnalPrecompiledHeaders.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "glm/gtc/type_ptr.hpp"

namespace Nocturnal
{
	Renderer::SceneData* Renderer::sSceneData = new Renderer::SceneData;
	
	void Renderer::BeginScene(Camera& camera)
	{
		sSceneData->ViewMatrix = camera.GetViewMatrix();
		sSceneData->ProjectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetMatrix4(static_cast<char*>("model"), 1, 
			false, glm::value_ptr(sSceneData->ModelMatrix));
		shader->SetMatrix4(static_cast<char*>("view"), 1, 
			false, glm::value_ptr(sSceneData->ViewMatrix));
		shader->SetMatrix4(static_cast<char*>("projection"), 1, 
			false, glm::value_ptr(sSceneData->ProjectionMatrix));
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
