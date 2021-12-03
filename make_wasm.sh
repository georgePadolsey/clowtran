cd web_js_nextjs/public
emcc ../../src/wasm_driver.cpp -s WASM=1 --bind
cd ../..