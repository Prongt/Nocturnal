#include "NocturnalPrecompiledHeaders.h"
#include "ImGuiLayer.h"

#include "GLFW/glfw3.h"
#include "Nocturnal/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Nocturnal
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& imGuiIo = ImGui::GetIO();
		imGuiIo.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		imGuiIo.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//Default ImGui Keycodes 
		imGuiIo.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		imGuiIo.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		imGuiIo.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		imGuiIo.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		imGuiIo.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		imGuiIo.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		imGuiIo.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		imGuiIo.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		imGuiIo.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		imGuiIo.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		imGuiIo.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		imGuiIo.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		imGuiIo.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		imGuiIo.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		imGuiIo.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		imGuiIo.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		imGuiIo.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		imGuiIo.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		imGuiIo.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		imGuiIo.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		imGuiIo.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		imGuiIo.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init();
		
	}
	
	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& imGuiIo = ImGui::GetIO();
		Application& app = Application::Get();
		imGuiIo.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		imGuiIo.DeltaTime = deltaTime > 0.0f ? (time - deltaTime) : (1.0f / 60.0f);
		deltaTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}
