
build:
	g++ -std=c++17 linkscript/src/*.cpp -I./linkscript/include -lm -o build/standalone/ls_standalone
build_wasm:
	em++ linkscript/src/*.cpp -o build/wasm/afx.js \
		-Ilinkscript/include \
		-I/home/toharxp/Projects/raylib/src/ \
		-O2 \
		-s WASM=1 \
		-s MODULARIZE=1 \
		-s EXPORT_NAME="AFXRuntime" \
		-s EXPORTED_FUNCTIONS='["_runScript","_resetRuntime"]' \
		-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s USE_SDL=2 \
		-s LEGACY_GL_EMULATION \
		-DPLATFORM_WEB