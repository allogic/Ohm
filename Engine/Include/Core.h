#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <stack>

#define ENGINE_STR_HELPER(STR) #STR
#define ENGINE_STR(STR) ENGINE_STR_HELPER(STR)

#define ENGINE_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;

#define ENGINE_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define ENGINE_MEASURE_END(NAME) std::cout << ENGINE_STR(NAME)": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - NAME##_measure).count() << "ms" << std::endl;