#pragma once

#include "Core.h"
#include "WindowConfig.h"

#include <glfw/glfw3.h>

namespace Ohm {
	class CApplication;

	class CWindow final {
	public:
		CWindow(void* pApplication, const SWindowConfig& config);
		CWindow(const CWindow&) = delete;
		CWindow(CWindow&&) = delete;

		virtual ~CWindow();

	public:
		auto& operator =(const CWindow&) = delete;

	public:
		inline auto* Ptr() { return mpWindow; }

	private:
		GLFWwindow* mpWindow = nullptr;
	};
}