#pragma once

#include "Core.h"
#include "Window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ohm {
	class CGui final {
	public:
		CGui(const CWindow& window);
		CGui(const CGui&) = delete;
		CGui(CGui&&) = delete;

		~CGui();

	public:
		auto& operator =(const CGui&) = delete;

	public:
		void Begin() const;
		void End() const;
		void Render() const;
	};
}