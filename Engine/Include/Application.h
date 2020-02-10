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

		bool vsync;

		const char* title;
	};

	class CApplication {
	protected:
		CApplication(const SApplicationConfig& config);
		CApplication(const CApplication&) = delete;
		CApplication(CApplication&&) = delete;

		virtual ~CApplication();

	protected:
		auto& operator =(const CApplication&) = delete;

	public:
		void Run();

		inline void PushScene() {
			mScenes.emplace();
		}
		inline void PopScene() {
			mScenes.pop();
		}

		inline auto CreateEntity() { return mScenes.top().CreateEntity(); }

		template<typename Component, typename ... Args>
		inline void AddComponent(const entt::entity& entity, Args&&... args) {
			mScenes.top().AddComponent<Component>(entity, std::forward<Args>(args) ...);
		}

		template<typename ... Components>
		inline auto GetComponents(const entt::entity& entity) {
			return mScenes.top().GetComponents<Components>(entity);
		}

	protected:
		virtual void OnImGui(double deltaTime) {}

		virtual void OnUpdate(double deltaTime) {}
		virtual void OnFixedUpdate(double deltaTime) {}

		virtual void OnRender(double deltaTime) const {}

	private:
		friend int ::main(int argc, char** argv);

	private:
		static inline void ErrorCallback(int error, const char* message) { ENGINE_TRACE(message); }

		static inline void CloseCallback(GLFWwindow* pWindow) {
			auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			app->mRunning = false;
		}
		static inline void ResizeCallback(GLFWwindow* pWindow, int width, int height) {
			auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

			app->mConfig.width = width;
			app->mConfig.height = height;
		}

	private:
		void BeginEditorRootWindow();

		void Menu();
		void Hierarchy();
		void Scene();

	private:
		SApplicationConfig mConfig;

		GLFWwindow* mpWindow = nullptr;

		bool mRunning = true;

		std::stack<CScene> mScenes;
	};
}