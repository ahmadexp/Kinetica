Kinetica (macOS build)

Dependencies (recommended via Homebrew):

- Install Homebrew if needed: https://brew.sh/
- Install required packages:

```
brew install sdl sdl_image sdl_mixer glew
```

Build and run:

```
cd Kinetica
make
./Kinetica
```

Notes:
- The `Makefile` now detects macOS and uses `clang++` and macOS frameworks.
- If you use SDL2 or have libraries installed in nonstandard locations, adjust `sdl-config` or the `Makefile` include/library paths.
- The project includes OVR (Oculus) source; if you need the OVR runtime or SDK, install it separately and update linker flags.
