cd js_test
emcc ../src/wasm_driver.cpp -s WASM=1 --bind
cd ..