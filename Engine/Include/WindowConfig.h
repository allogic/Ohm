#pragma once

namespace Ohm {
	struct SWindowConfig {
		unsigned int antialiasing;

		unsigned int width;
		unsigned int height;

		const char* title;
	};
}