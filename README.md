# Raylib ECS Engine

A C++ game engine built on top of [raylib](https://www.raylib.com/), using an Entity-Component-System (ECS) architecture.
Includes a Flappy Bird sample game demonstrating the engine's features.

## Features

- **GameObject & Component system** — attach, retrieve and remove typed components on any game object
- **Scene management** — create/destroy GameObjects at runtime, unified `Start` / `Update` / `Render` loop
- **Transform system** — 2D world transform (`TransformComponent`) and UI rect transform (`RectTransformComponent`)
- **Camera** — `CameraComponent` with configurable background color and target tracking
- **Collision detection** — `CircleCollider` and `RectCollider` with `OnCollisionEnter` / `OnCollisionExit` callbacks
- **Renderers** — `CircleRenderer`, `RectRenderer`, `SpriteRenderer` for world-space objects
- **UI system** — `CanvasComponent`, `TextComponent`, `ImageComponent`, `ButtonComponent`
- **Input system** — centralised `Inputs` wrapper around raylib keyboard/mouse polling

## Supported Platforms

* Windows

## Building

### VSCode (all platforms)

* Open the folder in VSCode
* Run the build task (`Ctrl+Shift+B` or `F5`)

### Windows — MinGW-W64

```bat
build-MinGW-W64.bat
make
```

> Use a modern MinGW-W64 from [w64devkit](https://github.com/skeeto/w64devkit/releases) or the raylib installer.
> Make sure `C:\raylib\w64devkit\bin` is in your `PATH`.

### Windows — Visual Studio 2022

```bat
build-VisualStudio2022.bat
```

Then open the generated `.sln` file.

## Output

Built binaries are placed in the `bin/` directory.

## License

MIT License

Copyright (c) 2025 Yanis Annasri

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
