/*
* TODO:
*  o Finish deferred renderer with multiple passes
*  o Impl vars. light models/shaders
*  o Impl frame buffers for drawing routines
*/

#include "Application.h"

/*
* Header mess
*/
#include "Shaders/PhongShader.h"

extern Ohm::CApplication* Create();

#define CREATE(APP) Ohm::CApplication* Create() { return new APP; }

int main(int argc, char** argv) {
	try {
		auto* app = Create();

		if (app) app->Run();

		delete app;
	}
	catch (const std::exception & ex) {
		ENGINE_TRACE(ex.what());

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}