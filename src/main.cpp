#include "render.h"
#include <vector>
#include <string>

int main() {
    render();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    render_print_vector(vec);
}
