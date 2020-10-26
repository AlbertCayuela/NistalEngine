#pragma once
#define _USE_MATH_DEFINES

#include "Glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include <cmath>

using namespace std;

class CubeRender
{
public:
    CubeRender();

    void DrawCubeDirectMode();
    void DrawCubeVertexArray();
    void DrawCubeIndices();
};
