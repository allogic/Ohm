#include "Application.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Ohm::CApplication::CApplication(const SApplicationConfig& config) :
	mConfig(config) {
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit()) {
		ENGINE_TRACE("Failed initializing glfw");

		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ENGINE_GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ENGINE_GL_MINOR);
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mpWindow = glfwCreateWindow(static_cast<int>(mConfig.width), static_cast<int>(mConfig.height), mConfig.title, nullptr, nullptr);

	if (!mpWindow) {
		ENGINE_TRACE("Failed creating glfw window");

		return;
	}

	glfwMakeContextCurrent(mpWindow);

	glfwSetWindowUserPointer(mpWindow, this);

	glfwSetWindowCloseCallback(mpWindow, CloseCallback);
	glfwSetWindowSizeCallback(mpWindow, ResizeCallback);

	if (!gladLoadGL()) {
		ENGINE_TRACE("Failed loading gl");

		return;
	}

	if (!IMGUI_CHECKVERSION()) {
		ENGINE_TRACE("Failed imgui check");

		return;
	}

	if (!ImGui::CreateContext()) {
		ENGINE_TRACE("Failed creating imgui context");

		return;
	}

	InitImGui();

	if (!ImGui_ImplGlfw_InitForOpenGL(mpWindow, true)) {
		ENGINE_TRACE("Failed initializing imgui for glfw");

		return;
	}

	if (!ImGui_ImplOpenGL3_Init(ENGINE_GLSL_VERSION_STR)) {
		ENGINE_TRACE("Failed initializing imgui for gl");

		return;
	}
}

Ohm::CApplication::~CApplication() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwDestroyWindow(mpWindow);
	glfwTerminate();
}

void Ohm::CApplication::Run() {
	if (!mpWindow) return;

	double time = 0.;
	double prevTime = 0.;
	double deltaTime = 0.;

	const double renderRate = 1. / mConfig.framesPerSecond;
	double prevRenderTime = 0.;

	while (mRunning) {
		glfwPollEvents();

		time = glfwGetTime();
		deltaTime = time - prevTime;

		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();

			ImGui::NewFrame();
			InitImguiDockSpace();
			OnImGui(deltaTime);
			ImGui::EndFrame();

			ImGui::Render();

			glViewport(0, 0, mConfig.width, mConfig.height);
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			glfwSwapBuffers(mpWindow);
		}

		OnUpdate(deltaTime);

		mScene.Update(deltaTime);

		if ((time - prevRenderTime) >= renderRate) {
			OnRender(deltaTime);

			mScene.Render(deltaTime);

			glfwSwapBuffers(mpWindow);

			prevRenderTime = time;
		}

		prevTime = time;
	}
}

void Ohm::CApplication::InitImGui() {
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

	io.ConfigDockingWithShift = true;

	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
}

void Ohm::CApplication::InitImguiDockSpace() {
	ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

	dockSpaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;

	windowFlags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("Root", 0, windowFlags);

	//ImGui::ShowDemoWindow((bool*)1);

	//Menu();

	ImGui::DockSpace(ImGui::GetID("Hierarchy"), ImVec2(0.0f, 0.0f), dockSpaceFlags);

	//Hierarchy();
	//Scene();

	ImGui::End();
}

void Ohm::CApplication::Menu() {
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene")) {
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void Ohm::CApplication::Hierarchy() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;

	windowFlags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	ImGui::Begin("Hierarchy", 0, windowFlags);

	ImGui::Text("this is some foo");

	ImGui::End();
}

void Ohm::CApplication::Scene() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;

	windowFlags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	ImGui::Begin("Scene", 0, windowFlags);

	ImGui::Text("this is some bar");

	ImGui::End();
}