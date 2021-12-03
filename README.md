# [WIP] C-LOWTRAN

This is a (WIP) version of LOWTRAN7 which has been translated into C++17 with bindings available for Python (outputting numpy arrays) and Javascript (via WASM).

In it's current state, it is able to run the  cards such as in the traditional LOWTRAN model.

As is clear from the lack of documentation in this README. This project is in the very early stages. Though it now has the same capability as the [SpacePhysics python](https://github.com/space-physics/lowtran) bindings.

## Building

For python and C++ bindings -- CMake

`cmake .`

For WASM (Javascript), requires emscripten

`./make_wasm.sh` which will build it to `web_js_nextjs/public`


Credit to:
- The original LOWTRAN creators
- [SpacePhysics](https://github.com/space-physics/) - who created the original LOWTRAN python bindings