/*
* TODO:
*  - impl framebuffers!
*  - remove configs!
*  - impl imgui docking
*  - impl lambert render call!!
*/

#include "Application.h"

extern Ohm::CApplication* Create();

#define CREATE(APP) Ohm::CApplication* Create() { return new APP; }

int main(int argc, char** argv) {
	try {
		auto* app = Create();

		app->Run();

		delete app;
	}
	catch (const std::exception & ex) {
		ENGINE_TRACE(ex.what());

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}