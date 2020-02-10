#pragma once
#pragma once

#include <glad/glad.h>

#include "Core.h"
#include "Scene.h"
#include "Window.h"
#include "ApplicationConfig.h"
#include "WindowConfig.h"

#include <glfw/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main(int argc, char** argv);

namespace Ohm {
	class CWindow;

	class CApplication {
		friend int ::main(int argc, char** argv);

	protected:
		CApplication(
			const SApplicationConfig& applicationConfig,
			const SWindowConfig& windowConfig);
		CApplication(const CApplication&) = delete;
		CApplication(CApplication&&) = delete;

		virtual ~CApplication();

	protected:
		auto& operator =(const CApplication&) = delete;

	public:
		void Run();

		inline void PushScene() { mScenes.emplace(); }
		inline void PopScene() { mScenes.pop(); }

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
		void BeginEditorRootWindow();

		void Menu();
		void Hierarchy();
		void Scene();

	private:
		SApplicationConfig mApplicationConfig;
		SWindowConfig mWindowConfig;

		CWindow mWindow;

		bool mRunning = true;

		std::stack<CScene> mScenes;
	};
}