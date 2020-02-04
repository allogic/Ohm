#pragma once

#include "Core.h"
#include "Scene.h"
#include "Event.h"

#include <glad/glad.h>

#include <glfw/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

int main(int argc, char** argv);

namespace Ohm {
	class CApplication {
	private:
		using TEventClbFuncPtr = void (CApplication::*)(const SEvent&);

	protected:
		CApplication(
			unsigned int framesPerSecond,
			unsigned int width,
			unsigned int height,
			const char* title);
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
		virtual void OnEvent(const SEvent& event) {};

	protected:
		inline const glm::ivec2& WindowSize() const { return mWindowSize; }
		inline const glm::vec2& MousePosition() const { return mMousePosition; }

	private:
		friend int ::main(int argc, char** argv);

	private:
		static inline void ErrorCallback(int error, const char* message) { ENGINE_TRACE(message); }

		static inline void CloseCallback(GLFWwindow* pWindow) {
			CApplication* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			SEvent event;

			event.category = TEventCategory::WindowEvent;
			event.type = TEventType::WindowClose;

			app->OnEvent(event);
		}
		static inline void ResizeCallback(GLFWwindow* pWindow, int width, int height) {
			CApplication* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			app->mWindowSize = { width, height };
		}
		static inline void MousePositionCallback(GLFWwindow* pWindow, double x, double y) {
			CApplication* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			app->mMousePosition = { static_cast<float>(x), static_cast<float>(y) };
		}

	private:
		void EventCallback(const SEvent& event);

		void InitImGui();

		void DrawEditor();

		void EditorMenu();
		void EditorHierarchy();
		void EditorScene();

	private:
		unsigned int mFramesPerSecond;

		GLFWwindow* mpWindow = nullptr;

		bool mRunning = true;

		glm::ivec2 mWindowSize;
		glm::vec2 mMousePosition{};

		TEventClbFuncPtr mpEventClbFuncPtr = nullptr;

	public:
		CScene mScene;
	};
}