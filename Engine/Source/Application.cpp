#include "Application.h"

#include <glad/glad.h>

Ohm::CApplication::CApplication(const SApplicationConfig& applicationConfig, const SWindowConfig& windowConfig) :
	mApplicationConfig(applicationConfig),
	mWindowConfig(windowConfig),
	mWindow(this, windowConfig),
	mGui(mWindow) {

}

void Ohm::CApplication::Run() {
	if (!mWindow.Ptr()) return;

	double time = 0.;
	double prevTime = 0.;
	double deltaTime = 0.;

	const double renderRate = 1. / mApplicationConfig.framesPerSecond;
	double prevRenderTime = 0.;

	glfwSwapInterval(mApplicationConfig.vsync);

	while (mRunning) {
		glfwPollEvents();

		time = glfwGetTime();
		deltaTime = time - prevTime;

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		mGui.Begin();

		BeginEditorRootWindow();

		OnUpdate(deltaTime);
		mScenes.top().Update(deltaTime);

		if ((time - prevRenderTime) >= renderRate) {
			OnFixedUpdate(deltaTime);
			mScenes.top().FixedUpdate(deltaTime);

			OnRender(deltaTime);
			mScenes.top().Render(deltaTime);

			prevRenderTime = time;
		}

		EndEditorRootWindow();

		mGui.End();

		glViewport(0, 0, mWindowConfig.width, mWindowConfig.height);

		mGui.Render();

		glfwSwapBuffers(mWindow.Ptr());

		prevTime = time;
	}
}

void Ohm::CApplication::BeginEditorRootWindow() {
	ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;
	dockSpaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
	windowFlags |= ImGuiWindowFlags_NoBackground;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoCollapse;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoMove;

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("Root", 0, windowFlags);

	ImGuiID rootId = ImGui::GetID("Root");

	ImGui::DockSpace(rootId, ImVec2(0.0f, 0.0f), dockSpaceFlags);
}

void Ohm::CApplication::EndEditorRootWindow() {
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