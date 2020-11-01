#include "Globals.h"
#include "cubeEngine.h"

CubeRender::CubeRender()
{

}

void CubeRender::DrawCubeDirectMode()
{
    //Creating a cube
    glBegin(GL_TRIANGLES);

    //1
    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 0.f, 0.f); //a						
    glTexCoord2f(1.0, 0.0);  glVertex3f(0.f, 0.f, 0.f);  //b
    glTexCoord2f(0.0, 1.0);  glVertex3f(-2.f, 2.f, 0.f); //c

    glTexCoord2f(0.0, 1.0);  glVertex3f(-2.f, 2.f, 0.f); //c
    glTexCoord2f(1.0, 0.0);  glVertex3f(0.f, 0.f, 0.f);  //b
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 2.f, 0.f);  //d

    //2
    glTexCoord2f(1.0, 0.0);  glVertex3f(0.f, 0.f, 0.f);  //b
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 0.f, -2.f);  //f
    glTexCoord2f(0.0, 0.0);  glVertex3f(0.f, 2.f, 0.f);  //d

    glTexCoord2f(0.0, 0.0);  glVertex3f(0.f, 2.f, 0.f);  //d
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 0.f, -2.f); //f
    glTexCoord2f(0.0, 1.0);  glVertex3f(0.f, 2.f, -2.f); //h

    //2
    glTexCoord2f(1.0, 0.0);  glVertex3f(-2.f, 2.f, 0.f);
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 2.f, 0.f);
    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 2.f, -2.f); //g

    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 2.f, -2.f);
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 2.f, 0.f);
    glTexCoord2f(0.0, 1.0);  glVertex3f(0.f, 2.f, -2.f);

    //2
    glTexCoord2f(1.0, 0.0);  glVertex3f(-2.f, 0.f, -2.f); //e
    glTexCoord2f(1.0, 1.0);  glVertex3f(-2.f, 0.f, 0.f);
    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 2.f, -2.f);

    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 2.f, -2.f);
    glTexCoord2f(1.0, 1.0);  glVertex3f(-2.f, 0.f, 0.f);
    glTexCoord2f(0.0, 1.0);  glVertex3f(-2.f, 2.f, 0.f);

    //1
    glTexCoord2f(0.0, 0.0);  glVertex3f(0.f, 0.f, -2.f);
    glTexCoord2f(1.0, 0.0);  glVertex3f(-2.f, 0.f, -2.f);
    glTexCoord2f(0.0, 1.0);  glVertex3f(0.f, 2.f, -2.f);

    glTexCoord2f(0.0, 1.0);  glVertex3f(0.f, 2.f, -2.f);
    glTexCoord2f(1.0, 0.0);  glVertex3f(-2.f, 0.f, -2.f);
    glTexCoord2f(1.0, 1.0);  glVertex3f(-2.f, 2.f, -2.f);

    //2
    glTexCoord2f(1.0, 0.0);  glVertex3f(-2.f, 0.f, -2.f);
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 0.f, -2.f);
    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 0.f, 0.f);

    glTexCoord2f(0.0, 0.0);  glVertex3f(-2.f, 0.f, 0.f);
    glTexCoord2f(1.0, 1.0);  glVertex3f(0.f, 0.f, -2.f);
    glTexCoord2f(0.0, 1.0);  glVertex3f(0.f, 0.f, 0.f);

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

