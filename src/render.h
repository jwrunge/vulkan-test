#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define RENDER_EXPORT __declspec(dllexport)
#else
  #define RENDER_EXPORT
#endif

RENDER_EXPORT void render();
RENDER_EXPORT void render_print_vector(const std::vector<std::string> &strings);
