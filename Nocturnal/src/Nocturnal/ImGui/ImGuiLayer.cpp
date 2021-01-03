#include "NocturnalPrecompiledHeaders.h"
#include "ImGuiLayer.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

//TODO Remove headers 
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
		imGuiIo.KeyMap[ImGuiKey_Tab] =			(int)KeyCode::Tab;
		imGuiIo.KeyMap[ImGuiKey_LeftArrow] =	(int)KeyCode::LeftArrow;
		imGuiIo.KeyMap[ImGuiKey_RightArrow] =	(int)KeyCode::RightArrow;
		imGuiIo.KeyMap[ImGuiKey_UpArrow] =		(int)KeyCode::UpArrow;
		imGuiIo.KeyMap[ImGuiKey_DownArrow] =	(int)KeyCode::DownArrow;
		imGuiIo.KeyMap[ImGuiKey_PageUp] =		(int)KeyCode::PageUp;
		imGuiIo.KeyMap[ImGuiKey_PageDown] =		(int)KeyCode::PageDown;
		imGuiIo.KeyMap[ImGuiKey_Home] =			(int)KeyCode::Home;
		imGuiIo.KeyMap[ImGuiKey_End] =			(int)KeyCode::End;
		imGuiIo.KeyMap[ImGuiKey_Insert] =		(int)KeyCode::Insert;
		imGuiIo.KeyMap[ImGuiKey_Delete] =		(int)KeyCode::DeleteKey;
		imGuiIo.KeyMap[ImGuiKey_Backspace] =	(int)KeyCode::Backspace;
		imGuiIo.KeyMap[ImGuiKey_Space] =		(int)KeyCode::Space;
		imGuiIo.KeyMap[ImGuiKey_Enter] =		(int)KeyCode::Enter;
		imGuiIo.KeyMap[ImGuiKey_Escape] =		(int)KeyCode::Escape;
		imGuiIo.KeyMap[ImGuiKey_KeyPadEnter] =	(int)KeyCode::NumPadEnter;
		imGuiIo.KeyMap[ImGuiKey_A] =			(int)KeyCode::A;
		imGuiIo.KeyMap[ImGuiKey_C] =			(int)KeyCode::C;
		imGuiIo.KeyMap[ImGuiKey_V] =			(int)KeyCode::V;
		imGuiIo.KeyMap[ImGuiKey_X] =			(int)KeyCode::X;
		imGuiIo.KeyMap[ImGuiKey_Y] =			(int)KeyCode::Y;
		imGuiIo.KeyMap[ImGuiKey_Z] =			(int)KeyCode::Z;

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

		const float time = (float)glfwGetTime();
		imGuiIo.DeltaTime = DeltaTime > 0.0f ? (time - DeltaTime) : (1.0f / 60.0f);
		DeltaTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher (event);
		dispatcher.Dispatch<KeyDownEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyDownEvent));
		dispatcher.Dispatch<KeyUpEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyUpEvent));
		dispatcher.Dispatch<KeyTypedEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<MouseButtonDownEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseDownEvent));
		dispatcher.Dispatch<MouseButtonUpEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseUpEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<MouseMovedEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(NOC_BIND_EVENT_FUNCTION(ImGuiLayer::OnWindowResizeEvent));
		
		
		//// Modifiers are not reliable across systems
		
		
	}

	bool ImGuiLayer::OnKeyDownEvent(KeyDownEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[(int)KeyCode::LeftControl] || io.KeysDown[(int)KeyCode::RightControl];
		io.KeyShift = io.KeysDown[(int)KeyCode::LeftShift] || io.KeysDown[(int)KeyCode::RightShift];
		io.KeyAlt = io.KeysDown[(int)KeyCode::LeftAlt] || io.KeysDown[(int)KeyCode::RightAlt];
		io.KeySuper = io.KeysDown[(int)KeyCode::LeftWindows] || io.KeysDown[(int)KeyCode::RightWindows];

		return false;
	}

	bool ImGuiLayer::OnKeyUpEvent(KeyUpEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		const int keycode = event.GetKeyCode();

		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter(static_cast<unsigned short>(keycode));
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MousePos = ImVec2(event.GetX(), event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseDownEvent(MouseButtonDownEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseReleased[event.GetMouseButton()] = false;
		io.MouseDown[event.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseUpEvent(MouseButtonUpEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseReleased[event.GetMouseButton()] = true;
		io.MouseDown[event.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel += event.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		
		return false;
	}
}
