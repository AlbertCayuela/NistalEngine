#pragma once
#include "Globals.h"
#include "cubeEngine.h"

CubeRender::CubeRender()
{

}

void CubeRender::DrawCubeDirectMode()
{
    //Creating a cube
    glBegin(GL_TRIANGLES);

    glVertex3f(-1.0f, 1.0f, 0.0f);//c
    glVertex3f(0.0f, 1.0f, 0.0f);//d
    glVertex3f(-1.0f, 1.0f, -1.0f);//g

    glVertex3f(0.0f, 1.0f, 0.0f);//d
    glVertex3f(0.0f, 1.0f, -1.0f);//h
    glVertex3f(-1.0f, 1.0f, -1.0f);//g

    glVertex3f(-1.0f, 0.0f, 0.0f);//a
    glVertex3f(0.0f, 0.0f, 0.0f);//b
    glVertex3f(-1.0f, 1.0f, 0.0f);//c

    glVertex3f(0.0f, 0.0f, 0.0f);//b
    glVertex3f(0.0f, 1.0f, 0.0f);//d
    glVertex3f(-1.0f, 1.0f, 0.0f);//c

    glVertex3f(0.0f, 0.0f, 0.0f);//b
    glVertex3f(0.0f, 0.0f, -1.0f);//f
    glVertex3f(0.0f, 1.0f, 0.0f);//d

    glVertex3f(0.0f, 0.0f, -1.0f);//f
    glVertex3f(0.0f, 1.0f, -1.0f);//h
    glVertex3f(0.0f, 1.0f, 0.0f);//d

    glVertex3f(-1.0f, 0.0f, 0.0f);//a
    glVertex3f(-1.0f, 1.0f, 0.0f);//c
    glVertex3f(-1.0f, 0.0f, -1.0f);//e

    glVertex3f(-1.0f, 0.0f, -1.0f);//e
    glVertex3f(-1.0f, 1.0f, 0.0f);//c
    glVertex3f(-1.0f, 1.0f, -1.0f);//g

    glVertex3f(0.0f, 0.0f, -1.0f);//f
    glVertex3f(-1.0f, 0.0f, -1.0f);//e
    glVertex3f(0.0f, 1.0f, -1.0f);//h

    glVertex3f(-1.0f, 0.0f, -1.0f);//e
    glVertex3f(-1.0f, 1.0f, -1.0f);//g
    glVertex3f(0.0f, 1.0f, -1.0f);//h

    glVertex3f(0.0f, 0.0f, 0.0f);//b
    glVertex3f(-1.0f, 0.0f, 0.0f);//a
    glVertex3f(-1.0f, 0.0f, -1.0f);//e

    glVertex3f(0.0f, 0.0f, 0.0f);//b
    glVertex3f(-1.0f, 0.0f, -1.0f);//e
    glVertex3f(0.0f, 0.0f, -1.0f);//f
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnd();
}

void CubeRender::DrawCubeVertexArray()
{
    float vertices[6 * 9 * 2] = // Size its = 6 faces * 9 vertex * 2 triangles 
    {
        // Face 1
        0.f, 0.f, 0.f,
        0.f, 0.f, 1.f,
        0.f, 1.f, 0.f,

        0.f, 0.f, 1.f,
        0.f, 1.f, 1.f,
        0.f, 1.f, 0.f,

        // Face 2
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f,
        0.f, 1.f, 1.f,

        1.f, 0.f, 1.f,
        1.f, 1.f, 1.f,
        0.f, 1.f, 1.f,

        // Face 3
        1.f, 0.f, 1.f,
        1.f, 0.f, 0.f,
        1.f, 1.f, 0.f,

        1.f, 0.f, 1.f,
        1.f, 1.f, 0.f,
        1.f, 1.f, 1.f,


        // Face 4
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        1.f, 1.f, 0.f,

        0.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        1.f, 0.f, 0.f,


        // Face 5
        0.f, 1.f, 0.f,
        0.f, 1.f, 1.f,
        1.f, 1.f, 0.f,

        1.f, 1.f, 1.f,
        1.f, 1.f, 0.f,
        0.f, 1.f, 1.f,


        // Face 6
        0.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        0.f, 0.f, 1.f,

        1.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 0.f
    };

    GLuint my_id = 0;
    glGenBuffers(1, &my_id);
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 9 * 2, vertices, GL_STATIC_DRAW);// 6 faces * 9 vertex * 2 triangles 
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    // draw other buffers
    glDrawArrays(GL_TRIANGLES, 0, (6 * 9 * 2) / 3); // 6 faces * 9 vertex * 2 triangles / 3 vertex per triangle
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CubeRender::DrawCubeIndices()
{
    static float vertex[] = {
                            1.0f, 1.0f, 1.0f, //v0 
                            -1.0f, 1.0f, 1.0f, //v1
                            -1.0f, -1.0f, 1.0f, //v2
                            1.0f, -1.0f, 1.0f, //v3
                            1.0f, -1.0f, -1.0f, //v4
                            1.0f, 1.0f, -1.0f, //v5
                            -1.0f, 1.0f, -1.0f, //v6
                            -1.0f, -1.0f, -1.0f //v7
    };
    static uint indices[] = { //Front
                              0, 1, 2,
                              2, 3, 0,
                              //Right
                              0, 3, 4,
                              4, 5, 0,
                              //Up
                              0, 5, 6,
                              6, 1, 0,
                              //Back
                              7, 6, 5,
                              5, 4, 7,
                              //Left
                              7, 2, 1,
                              1, 6, 7,
                              //Back
                              7, 4, 3,
                              3, 2, 7
    };

    //Vertex
    uint vert_id = 0;
    glGenBuffers(1, (GLuint*)&(vert_id));
    glBindBuffer(GL_ARRAY_BUFFER, vert_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Index
    uint ind_id = 0;
    glGenBuffers(1, (GLuint*)&(ind_id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Draw
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vert_id);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_id);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}
