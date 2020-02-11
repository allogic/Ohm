#include "Gui.h"

Ohm::CGui::CGui(const CWindow& window) {
	if (!IMGUI_CHECKVERSION()) {
		ENGINE_TRACE("Failed imgui check");

		return;
	}

	if (!ImGui::CreateContext()) {
		ENGINE_TRACE("Failed creating imgui context");

		return;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

	io.ConfigDockingWithShift = true;

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.f;
	style.WindowBorderSize = 0.f;

	style.Colors[ImGuiCol_WindowBg].w = 1.f;

	if (!ImGui_ImplGlfw_InitForOpenGL(window.Ptr(), true)) {
		ENGINE_TRACE("Failed initializing imgui for glfw");

		return;
	}

	if (!ImGui_ImplOpenGL3_Init(ENGINE_GLSL_VERSION_STR)) {
		ENGINE_TRACE("Failed initializing imgui for gl");

		return;
	}
}

Ohm::CGui::~CGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
}

void Ohm::CGui::Begin() const {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
}

void Ohm::CGui::End() const {
	ImGui::EndFrame();
}

void Ohm::CGui::Render() const {
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	GLFWwindow* context = glfwGetCurrentContext();

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();

	glfwMakeContextCurrent(context);
}