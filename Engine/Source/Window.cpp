#include "Window.h"

Ohm::CWindow::CWindow(void* pApplication, const SWindowConfig& config) {
	glfwSetErrorCallback([](int error, const char* msg) {
		ENGINE_TRACE(msg);
		});

	if (!glfwInit()) {
		ENGINE_TRACE("Failed initializing glfw");

		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, static_cast<int>(config.glMajor));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, static_cast<int>(config.glMinor));
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
	
		//app->mRunning = false;
		});
	glfwSetWindowSizeCallback(mpWindow, [](GLFWwindow* pWindow, int width, int height) {
		auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));
	
		//app->mConfig.width = width;
		//app->mConfig.height = height;
		});
}

Ohm::CWindow::~CWindow() {
	glfwDestroyWindow(mpWindow);

	glfwTerminate();
}