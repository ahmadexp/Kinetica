# Kinetica: The Virtual House

A high-performance 3D engine and game built using C++, OpenGL, and SDL2, designed with stereoscopic VR (HMD) support and cross-platform compatibility.

<img width="803" height="627" alt="Screenshot 2025-12-30 at 7 30 40 PM" src="https://github.com/user-attachments/assets/5dc210d2-b13a-4918-9782-e3cd98e310f3" />

## Features

- **Advanced 3D Rendering:** Optimized tile-based world system using OpenGL 2.1.
- **Dynamic Assets:** Loads models (OBJ, MS3D) and textures (BMP, PNG) with automatic platform-specific color correction.
- **VR Support:** Optional Head-Mounted Display (HMD) mode with lens distortion rectification and stereoscopic rendering.
- **Rich UI:** Premium in-game dashboard with real-time stats, mini-map, and help menus.
- **Custom Physics:** Includes collision detection, gravity, and a "Ghost Mode" for libre navigation.
- **Configurable:** Fully customizable via `settings.ini` for resolution, FOV, VR mode, and graphical fidelity.

## Controls

| Key | Action |
| :--- | :--- |
| **W / S** or **Up / Down** | Move Forward / Backward |
| **A / D** or **Left / Right** | Turn Left / Right |
| **Space** | Jump |
| **1** | Decrease Field of View (FOV) |
| **2** | Increase Field of View (FOV) |
| **3** | Toggle Textures ON/OFF |
| **4** | Toggle Ghost Mode ON/OFF |
| **5 / 6** | Cycle World Tiles (Edit Mode) |
| **7** | Rotate World Tile (Edit Mode) |
| **8 / 9** | Save / Load World State |
| **M** | Toggle Mouse Control |
| **P** | Toggle Third Person View (Show Player) |
| **G** | Toggle GPS Minimap |
| **Esc / Q** | Open Menu / Quit |

## Configuration (`settings.ini`)

You can modify the following parameters in `settings.ini`:

- `screenw` / `screenh`: Window resolution.
- `fullscreen`: Set to `1` for full screen, `0` for windowed.
- `usehmd`: Enable (`1`) or Disable (`0`) stereoscopic VR mode.
- `fov`: Default Field of View (e.g., `60`).
- `antialiasing` / `mipmapping`: Graphic quality toggles.

## Building and Running

### Prerequisites
- C++ Compiler (GCC/Clang)
- SDL2, SDL2_image, SDL2_mixer
- GLEW, OpenGL
- Ninja (preferred build system)

| Platform | Dependencies | Install Command |
|----------|--------------|-----------------|
| **macOS** | `brew`, `meson`, `ninja`, `glfw`, `glew`, `sdl2`, `pkg-config`, `sdl2_image` | `brew install meson ninja glfw glew sdl2_image sdl2 Pkg-config` |
| **Linux** | `meson`, `ninja`, `glfw`, `pkg-config`, `libxrandr-dev`, `libxinerama-dev`, `libxcursor-dev`, `libxi-dev` | `sudo apt-get install meson ninja-build libx11-dev libgl1-mesa-dev pkg-config libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev` |
| **Windows**| `choco`, `meson`, `ninja`, `Visual Studio`, `pkgconfiglite` | `choco install meson ninja pkgconfiglite` |

### Building the Project

1.  **Configure the build:**
    ```bash
    meson setup build
    ```

2.  **Compile:**
    ```bash
    meson compile -C build
    ```

## 📂 Project Structure
- `/source`: Core engine and game logic.
- `/source/generic`: Platform-agnostic utilities (math, physics, input).
- `/source/sky`: Skybox components.
- `/Media`: Textures, models, and audio assets.
- `k.vert` / `k.frag`: VR distortion shaders.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0).

You are free to:

Share — copy and redistribute the material in any medium or format
Adapt — remix, transform, and build upon the material
Under the following terms:

Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made.
NonCommercial — You may not use the material for commercial purposes.
For full details, see: https://creativecommons.org/licenses/by-nc/4.0/

As the project creator, I reserve the right to use this material commercially or under any other terms.
