#pragma once

#include "Core.h"
#include "Scene.h"

#include <glad/glad.h>

#include <glfw/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main(int argc, char** argv);

namespace Ohm {
	struct SApplicationConfig {
		unsigned int framesPerSecond;

		unsigned int width;
		unsigned int height;

		const char* title;
	};

	class CApplication {
	protected:
		CApplication(const SApplicationConfig& config);
		CApplication(const CApplication&) = delete;
		CApplication(CApplication&&) = delete;

		virtual ~CApplication();

	protected:
		CApplication& operator =(const CApplication&) = delete;

	public:
		void Run();

	protected:
		virtual void OnImGui(double deltaTime) {};
		virtual void OnUpdate(double deltaTime) {};
		virtual void OnRender(double deltaTime) const {};

	private:
		friend int ::main(int argc, char** argv);

	private:
		static inline void ErrorCallback(int error, const char* message) { ENGINE_TRACE(message); }

		static inline void CloseCallback(GLFWwindow* pWindow) {
			CApplication* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			app->mRunning = false;
		}
		static inline void ResizeCallback(GLFWwindow* pWindow, int width, int height) {
			CApplication* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			app->mConfig.width = width;
			app->mConfig.height = height;
		}

	private:
		void InitImGui();
		void InitImguiDockSpace();

		void Menu();
		void Hierarchy();
		void Scene();

	private:
		SApplicationConfig mConfig;

		GLFWwindow* mpWindow = nullptr;

		bool mRunning = true;

	public:
		CScene mScene;
	};
}