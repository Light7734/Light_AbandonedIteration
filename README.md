# Light
~~A Cross-Platform, Cross-GraphicsAPI Game Engine~~

A game engine with Vulkan backend and emphasis on pixel art.

## New plan
I'm going to remove the support for DirectX & OpenGL, this engine will only implement Vulkan for performance and simplicity(not Vulkan's simplicity but simplicity of not having 3 GraphicsAPIs exposed using the same functions...)

But for the time being, I need to learn vulkan, so the engine will be in an unusable state

Many things need to be changed as well, and I do have a busy schedule, so it'll take a while.

## Supported Operating Systems
* Linux
* Windows (Fails to build ATM)
 
Will support:
* Mac

## Getting Started

### Prerequisites
* CMake (duh)
* C++ 20
* Vulkan 1.3 support

### Getting the project
```bash
    git clone --recurse-submodules https://github.com/Light7734/light
        # if you cloned non-recursively then run "git submodule update --init"
    mkdir light/build
    cd light/build
    cmake -DEXPORT_COMPILE_COMMANDS=1 .. && ln -fs ./compile_commands.json ../compile_commands.json
    cmake --build . -j20
```

hmu if you wanna chat Light7734#4652
