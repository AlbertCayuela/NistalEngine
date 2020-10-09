#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "Glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

    //App->camera->Move(vec3(0.0f, 0.0f, 0.0f));
    App->camera->LookAt(vec3(0, 0, 0));

    return ret;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{    
    PlanePrimitive p(0, 1, 0, 0);
    p.axis = true;
    p.Render();

    /*glLineWidth(2.0f);

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(-2.0f, 2.0f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(-4.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(-6.0f, 2.0f, 0.0f);
    glColor3f(0, 1, 1);
    glVertex3f(-8.0f, 0.0f, 0.0f);
    glEnd();

    glColor3b(255.0f, 0.0f, 0.0f);*/

    unsigned int g_VboHandle = 0;

    //glGenBuffers(1, &g_VboHandle);
    //glBindBuffer();


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

    glEnd();

    return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
    LOG("Unloading Intro scene");

    return true;
}

