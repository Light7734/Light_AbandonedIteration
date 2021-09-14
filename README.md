# Light
A Cross-Platform, Cross-GraphicsAPI Game Engine

## Supported Graphics APIs
* OpenGL
* DirectX

Will support:
* Vulkan (under development)
* Metal (maybe not...)

## Supported Operating Systems
* Windows
* Linux (Won't compile ATM)
 
Will support:
* Mac

## Getting Started

### Prerequisites
* OpenGL 4.5 or higher
* DirectX 11 support on Windows machines

### Getting the project
```bash
    git clone --recurse-submodules -j4 https://github.com/Light3039/Light <folder_name>
        # if you cloned non-recursively then run "git submodule update --init"
    cd <folder_name>/CMake
    cmake ..
```

## Acknowledgments
Huge thanks to these people:
* [TheCherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw) for teaching C++, OpenGL and GameEngine development
* [Chili](https://www.youtube.com/channel/UCsyHonfwHi4fLb2lkq0DEAA) for teaching DirectX
* [JoeyDeVriez](https://learnopengl.com/) for creating learnopengl.com
