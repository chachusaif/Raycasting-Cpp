# Raycaster

A Wolfenstein-style raycasting engine written from scratch in C++ with Raylib.

## About

A pseudo-3D renderer built without a 3D engine. The world is a 2D grid; the illusion of depth comes from casting one ray per screen column, finding the first wall each ray hits, and drawing a vertical strip whose height is inversely proportional to the distance.

Everything above the platform layer is written by hand: the renderer, the camera model, the coordinate system and collision. Raylib provides window creation, input polling and pixel output; it is not doing the rendering.

## Current state

- [X] Grid-marching DDA raycaster (`castRay`)
- [X] Perspective-correct wall rendering with fisheye correction
- [ ] Per-side wall shading
- [X] Per-tile wall colours
- [ ] Mouse look and WASD movement
- [ ] Sliding wall collision
- [ ] FPS counter

## Roadmap

**Next**

- Textured walls
- Sprites and depth buffering
- Floor and ceiling casting

**Later**

- Enemy types and basic AI
- Multiple levels
- Developer mode with an in-engine level editor
- Community level uploads
- Cloud-hosted web front end

## Building

### Prerequisites

| Tool | Version used |
| --- | --- |
| C++ compiler | GCC 16.1.0 (MSYS2) |
| Raylib | 5.5.0 |
| CMake | 4.3.4 |

### Steps

```bash
git clone https://github.com/chachusaif/Raycasting-Cpp.git
cd Raycasting-Cpp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The executable lands in `build/`.

> Build in `Release` for anything other than debugging. A `Debug` build is several times slower and will make the frame rate look far worse than it is.

## Controls

| Input | Action |
| --- | --- |
| `W` / `S` | Move forward / back |
| `A` / `D` | Strafe left / right |
| Mouse | Look |
| `Esc` | Release cursor |

## How it works

**Camera model.** The player holds a unit direction vector and a perpendicular camera plane vector. The ratio of their lengths sets the field of view. Turning rotates both by the same angle, so they stay perpendicular and the FOV is constant.

**Ray directions.** Each screen column `x` maps to a value `cameraX` in the range −1 to +1, and the ray direction is `dir + plane * cameraX`. Because the rays sample a flat plane rather than an arc, the projection stays correct at the screen edges.

**Grid marching.** The DDA steps from grid boundary to grid boundary rather than in fixed increments, so each step is exact and a ray crossing eight cells costs eight map lookups. The distance it accumulates is already perpendicular to the camera plane, which is what prevents fisheye distortion without any explicit cosine correction.

**Projection.** Wall strip height is `screenHeight / perpWallDist`, centred on the horizon.

## Project structure

```
.
├── main.cpp
├── CMakeLists.txt
└── build/          # generated, not tracked
```

## Acknowledgements

- [Lode Vandevenne's raycasting tutorial](https://lodev.org/cgtutor/raycasting.html) — the canonical reference for this technique
- [Raylib](https://www.raylib.com/) — windowing, input and rendering platform

## License

MIT
