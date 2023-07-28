# Build

```
git clone https://github.com/fahlerile/opengl-minecraft-clone.git
cd opengl-minecraft-clone
mkdir build
cd build
cmake ..
make
cd bin
./minecraft.exe
```

# Exit codes

- `1` - Failed to initialize GLFW
- `2` - Failed to initialize GLEW
- `3` - Failed to create a window

# Problems

40-50 FPS with 16x16x16 chunk of blocks

# TODO

- Optimization
    - Remove faces that see each other
    - Frustum culling
- Place/remove blocks
- Basic terrain generation
- Main menu & world saving
