#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleUI.h"
#include "sphereEngine.h"
#include "cubeEngine.h"

#include "Glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

    //App->load_fbx->LoadFBX(App->load_fbx->path);

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

    //TESTING CUBES
    CubeRender my_cube;

    if(App->ui->render_cube_direct_mode)
        my_cube.DrawCubeDirectMode();
    if (App->ui->render_cube_vertex)
        my_cube.DrawCubeVertexArray();
    if (App->ui->render_cube_indices)
        my_cube.DrawCubeIndices();

    //TESTING SPHERE RENDERING
    SphereRender my_sphere(1, 12, 24);

    if (App->ui->render_sphere)
        my_sphere.DrawSphere(0.0f, 0.0f, 0.0f);

    //DRAWING MODEL PROPERTIES
    if (App->ui->render_normals)
    {
        App->load_fbx->DrawNormals(App->load_fbx->model);
        App->load_fbx->DrawVertexNormals(App->load_fbx->model);
    }

    if (App->ui->render_texture)
    {
        //App->load_fbx->DrawTexture(App->load_fbx->model);
    }        

    return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
    App->load_fbx->DrawFBX(App->load_fbx->model);
    //App->load_fbx->DrawNormals(App->load_fbx->model);

    return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
    LOG("Unloading Intro scene");

    return true;
}