# LearnOpenGL
Execution of tutorials from https://learnopengl.com/ on MacOS Big Sur (on M1 chip)

## Overview of completed lessons
### Intro - Textures:
![Textured Quad](./docs/resources/floating_quad.gif)

### Intro - Transformations:
![Transformating Quad](./docs/resources/drunk_quad.gif)

### Intro - Spaces:
![3D Quads](./docs/resources/cubes.gif)

### Intro - Camera:
![Proper Fly Camera](./docs/resources/camera.gif)

## Build on Windows
Install vcpkg as described in 
https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd#1---set-up-vcpkg

Setup env variables
```
set VCPKG_ROOT="C:/path/to/vcpkg"
set PATH=%VCPKG_ROOT%;%PATH%
```

In the root dir run:

```
cmake --preset=default
cmake --build build
```
