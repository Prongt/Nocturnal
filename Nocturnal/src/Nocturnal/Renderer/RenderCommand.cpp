#include "NocturnalPrecompiledHeaders.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nocturnal
{
	RendererAPI* RenderCommand::s_RendererApi = new OpenGLRendererAPI;
}