#pragma once
namespace Nocturnal
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	private:
		static RendererAPI rendererAPI;
	public:
		inline static RendererAPI GetAPI() { return rendererAPI; }
	};
}