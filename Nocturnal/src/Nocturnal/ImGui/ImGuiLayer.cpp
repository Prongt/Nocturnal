#include "NocturnalPrecompiledHeaders.h"
#include "ImGuiLayer.h"

#include "GLFW/glfw3.h"
#include "Nocturnal/Application.h"
#include "Nocturnal/Events/KeyEvent.h"
#include "Nocturnal/Events/MouseEvent.h"
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
		ImGuiIO& io = ImGui::GetIO();

		const auto* keyPressed = dynamic_cast<KeyPressedEvent*>(&event);
		const auto* keyRelease = dynamic_cast<KeyReleasedEvent*>(&event);
		const auto* mouseMove = dynamic_cast<MouseMovedEvent*>(&event);
		const auto* mouseDown = dynamic_cast<MouseButtonPressedEvent*>(&event);
		const auto* mouseUp = dynamic_cast<MouseButtonReleasedEvent*>(&event);
		const auto* mouseScroll = dynamic_cast<MouseScrolledEvent*>(&event);


		if (keyPressed != nullptr)
		{
			io.KeysDown[keyPressed->GetKeyCode()] = true;
			NOC_CORE_TRACE("Key {0} was pressed", keyPressed->GetKeyCode());
		}

		if (keyRelease != nullptr)
		{
			io.KeysDown[keyRelease->GetKeyCode()] = false;
		}
		
		if (mouseMove != nullptr)
		{
			io.MousePos = ImVec2(mouseMove->GetX(), mouseMove->GetY());
		}

		if (mouseDown != nullptr)
		{
			io.MouseReleased[mouseDown->GetMouseButton()] = false;
			io.MouseDown[mouseDown->GetMouseButton()] = true;
		}

		if (mouseUp != nullptr)
		{
			io.MouseReleased[mouseUp->GetMouseButton()] = true;
			io.MouseDown[mouseUp->GetMouseButton()] = false;
		}

		if (mouseScroll != nullptr)
		{
			io.MouseWheelH += mouseScroll->GetXOffset();
			io.MouseWheel += mouseScroll->GetYOffset();
		}

		keyPressed = nullptr;
		keyRelease		= nullptr;
		mouseMove		= nullptr;
		mouseDown		= nullptr;
		mouseUp			= nullptr;
		mouseScroll		= nullptr;


		//// Modifiers are not reliable across systems
		//io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		//io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		//io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		
	}
}
