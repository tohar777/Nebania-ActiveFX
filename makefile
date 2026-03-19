
build:
	g++ -std=c++17 linkscript/src/*.cpp -I./linkscript/include -lm -o build/standalone/ls_standalone
build_wasm:
	em++ linkscript/src/*.cpp -o build/wasm/afx.js \
	-Ilinkscript/include \
	-O2 \
	-sMODULARIZE \
	-sEXPORT_NAME="AFXRuntime" \
	-sEXPORTED_FUNCTIONS=_runScript,_resetRuntime \
	-sEXPORTED_RUNTIME_METHODS=ccall,cwrap \
	-sALLOW_MEMORY_GROWTH