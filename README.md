# NistalEngine
Nistal Engine is a 3D Engine created in the third year of our Videogame Design and Development degree. It's mainly created using OPEN-GL.
In our Engine you will find an audio system too, that allows you to control audio sources, audio listeners, etc. We used Wwise system for the audio part.

You can check our GitHub repository here: https://github.com/AlbertCayuela/NistalEngine

### Version
Nistal Engine v.1.0

## Main Core Sub-Systems
### 3D Renderer
We mainly used OpenGL for the Engine Graphics. We use indices from OpenGL Arrays to draw everything.
(The primitives that you can load on the top menu they are all FBX pre-loaded).

## Geometry Loader
We load all the FBX information and we store it into buffers. Then we load this info and we use Assimp to get a 3D rendered object from this loaded data.

## Mouse Picking

## GameObjects System

## Serialization

## Time Management

## Instructions:
### Adding models
Drag an FBX from the "Models" folder to the engine viewport to create the hirearchy of gameobjects that represents it. If there's no gameobject selected, it will be son of the sceene. But if you have selected any gameobject and import a model, it will be son of this.
Gameobjects can be hidden through the inspector window.
### Mouse picking
Deploy any gameobject in the hierarchy and click "select" or click on the object.

In order to move an object select it and open the transform in the inspector.
## Controls
### General controls
- ESC: Quit
### Camera controls
- Movement: RightClick + WASD keys
- Pan / Zoom: Mouse wheel
- LeftAlt + LeftClick: Orbit around object
- F: Focus
- SHIFT: Duplicates movement speed
- RightClick + E: move camera up
- RightClick + R: move camera down

### Instructions to execute
1. Download the latest release from: https://github.com/AlbertCayuela/NistalEngine/releases
2. Unzip de file
3. Execute Nistal Engine.exe

### Team Members
### - Albert Cayuela: https://github.com/AlbertCayuela
- Hierarchy
- Time Manager
- Game Objects System
- Inspector
- Audio Part
- Frustum Culling
- Camera Component
- Mouse Picking
- Textures Loading
### - Nadine Gutiérrez: https://github.com/Nadine044
- Serialization
- Json Integration
- Save & Load Scenes
- Inspector
- Load FBX data (vertices, normals, textures...)
- Own File Format
- Parent/Unparent GameObjects

## Tools Used
- Visual Studio 2019
- OpenGL
- Assimp
- SDL
- Glew
- DeviL
- ImGui
- MathGeoLib
- Parson
- PhysFS

### License
MIT License

Copyright (c) 2020 Albert Cayuela & Nadine Gutiérrez

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
