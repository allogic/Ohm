#include "Application.h"
#include "Window.h"

Ohm::CWindow::CWindow(void* pApplication, const SWindowConfig& config) {
	glfwSetErrorCallback([](int error, const char* msg) {
		ENGINE_TRACE(msg);
		});

	if (!glfwInit()) {
		ENGINE_TRACE("Failed initializing glfw");

		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ENGINE_GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ENGINE_GL_MINOR);
	glfwWindowHint(GLFW_SAMPLES, static_cast<int>(config.antialiasing));
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mpWindow = glfwCreateWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title, nullptr, nullptr);

	if (!mpWindow) {
		ENGINE_TRACE("Failed creating glfw window");

		return;
	}

	glfwMakeContextCurrent(mpWindow);

	glfwSetWindowUserPointer(mpWindow, pApplication);

	glfwSetWindowCloseCallback(mpWindow, [](GLFWwindow* pWindow) {
		auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

		app->mRunning = false;
		});
	glfwSetWindowSizeCallback(mpWindow, [](GLFWwindow* pWindow, int width, int height) {
		auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));

		app->mWindowConfig.width = width;
		app->mWindowConfig.height = height;
		});
}

Ohm::CWindow::~CWindow() {
	glfwDestroyWindow(mpWindow);

	glfwTerminate();
}