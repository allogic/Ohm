#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#ifndef ENGINE_GL_MAJOR
#define ENGINE_GL_MAJOR 4
#endif

#ifndef ENGINE_GL_MINOR
#define ENGINE_GL_MINOR 0
#endif

#define ENGINE_STR_HELPER(STR) #STR
#define ENGINE_STR(STR) ENGINE_STR_HELPER(STR)

#define ENGINE_GLSL_VERSION_STR "#version " ENGINE_STR(ENGINE_GL_MAJOR) ENGINE_STR(ENGINE_GL_MINOR) "0"

#define ENGINE_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;

#define ENGINE_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define ENGINE_MEASURE_END(NAME) std::cout << ENGINE_STR(NAME)": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - NAME##_measure).count() << "ms" << std::endl;