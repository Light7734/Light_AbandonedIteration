# Light
A Cross-Platform, Cross-GraphicsAPI Game Engine

READ -> The engine is in a pretty broken condition right now, I haven't abandoned this project(yet), will resurrect this as soon as I am able to, thanks for your time

## Supported Graphics APIs
* OpenGL
* DirectX

Will support:
* Vulkan (under development)

## Supported Operating Systems
* Windows (Fails to build ATM)
* Linux
 
Will support:
* Mac (Get a real OS lol)

## Getting Started

### Prerequisites
* CMake (duh)
* C++ 20
* OpenGL 4.5 or higher

### Getting the project
```bash
    git clone --recurse-submodules https://github.com/Light3039/Light
        # if you cloned non-recursively then run "git submodule update --init"
    mkdir Light/build
    cd Light/build
    cmake ..
    cmake --build . -j20
```

hmu if you wanna chat Light7734#4652

## Acknowledgments
Huge thanks to these people:
* [TheCherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw) for teaching C++, OpenGL and GameEngine development
* [Chili](https://www.youtube.com/channel/UCsyHonfwHi4fLb2lkq0DEAA) for teaching DirectX
* [JoeyDeVriez](https://learnopengl.com/) for creating learnopengl.com
