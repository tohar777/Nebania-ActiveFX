#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(linklang_module) {
    function("run", &run);
}