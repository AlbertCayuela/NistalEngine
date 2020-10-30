#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleUI.h"
#include "sphereEngine.h"


#include "Glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "GameObject.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

    App->camera->Move(vec3(-5.0f, 3.5f, 0.0f));
    App->camera->LookAt(vec3(0, 0, 0));

    root = CreateGameObject(nullptr, "root");

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

    if (App->ui->render_cube_direct_mode)
    {
        App->scene_intro->my_cube.DrawCubeDirectMode();
    }        

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
        for (std::vector<modelData>::iterator i = App->load_fbx->meshes.begin(); i != App->load_fbx->meshes.end(); ++i)
        {
            //App->load_fbx->DrawNormals(*i);
            App->load_fbx->DrawVertexNormals(*i);
        }
        
    }       

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

GameObject* ModuleSceneIntro::CreateGameObject(GameObject* parent, const char* name)
{
    GameObject* game_object = new GameObject(parent, name);
    game_objects.push_back(game_object);
    LOG("Number of gameobjects in the scene: %i", game_objects.capacity());
    
    return game_object;
}
