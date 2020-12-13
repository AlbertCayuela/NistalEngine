#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleUI.h"
#include "GOMesh.h"
#include "GOMaterial.h"
#include "GOTransform.h"
#include "GOCamera.h"
#include "GameObject.h"
#include "ModuleSerialization.h"

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

    App->camera->Move(float3(-25.0f, 10.0f, -10.0f));
    App->camera->LookAt(float3(0, 0, 0));

    root = CreateGameObject(nullptr, "root");

    camera = CreateGameObject(root, "camera");
    camera->AddComponent(GOCOMPONENT_TYPE::CAMERA, "camera");
    camera->transform->NewPosition(float3(0.0f, 19.0f, -70.0f));
    camera->camera->SetFarPlane(200.0f);

    street = CreateGameObject(root, "Street");
    street->transform->NewRotation(float3(-90.0f, 0.0f, 0.0f));


    return ret;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
    App->playing_timer.UpdateTimer();
    return UPDATE_CONTINUE;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
    PlanePrimitive p(0, 1, 0, 0);
    p.axis = true;
    //to change size see p.innerrender() -> variable d(now its 10 it was 200 before)
    p.Render();

    if (!render_street)
    {
        App->load_fbx->LoadFBX("Models/Street environment_V01.fbx", street);
        //game_objects.at(2)->AddComponent(GOCOMPONENT_TYPE::MATERIAL, "texture");
        //game_objects.at(2)->material->LoadThisTex(App->load_fbx->texture_path);
        //game_objects.at(3)->AddComponent(GOCOMPONENT_TYPE::MATERIAL, "texture");
        //game_objects.at(3)->material->LoadThisTex(App->load_fbx->texture_path);
        render_street = true;
    }

    //PRIMITIVES
    if (App->ui->cube)
    {
        App->load_fbx->LoadFBX("Primitives/Cube.fbx");
        App->ui->cube = false;
    }

    if (App->ui->sphere)
    {
        App->load_fbx->LoadFBX("Primitives/Sphere.fbx");
        App->ui->sphere = false;
    }

    if (App->ui->cylinder)
    {
        App->load_fbx->LoadFBX("Primitives/Cylinder.fbx");
        App->ui->cylinder = false;
    }

    if (App->ui->cone)
    {
        App->load_fbx->LoadFBX("Primitives/Cone.fbx");
        App->ui->cone = false;
    }

    if (App->ui->torus)
    {
        App->load_fbx->LoadFBX("Primitives/Torus.fbx");
        App->ui->torus = false;
    }

    ImGui::Separator();

    root->Update(dt);

    //for (std::vector<GameObject*>::iterator i = own_game_objects.begin(); i != own_game_objects.end(); ++i)
    //{
    //    if ((*i)->has_mesh)
    //    {
    //        if((*i)->has_material)
    //            (*i)->mesh->DrawMesh((*i)->material->texture_id);
    //        else
    //            (*i)->mesh->DrawMesh(NULL);
    //    }
    //    if ((*i)->parent != nullptr)
    //    {
    //        if (!(*i)->parent->active)
    //        {
    //            (*i)->active = false;
    //        }
    //    }
    //}

    for (std::vector<GameObject*>::iterator i = game_objects.begin(); i != game_objects.end(); ++i)
    {
        if ((*i)->has_mesh)
        {
            (*i)->mesh->DrawMesh((*i)->material->texture_id);          
        }
        if ((*i)->parent != nullptr) 
        {
            if (!(*i)->parent->active)
            {
                (*i)->active = false;
            }
        }
    }

    if (App->ui->render_face_normals)
    {
         App->load_fbx->DrawNormals(selected_go->mesh->mesh_info);
    }

    if (App->ui->render_vertex_normals)
    {
        App->load_fbx->DrawVertexNormals(selected_go->mesh->mesh_info);
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
    
    return game_object;
}

GameObject* ModuleSceneIntro::CreateOWNGameObject(GameObject* parent, const char* name)
{
    GameObject* game_object = new GameObject(parent, name);
    own_game_objects.push_back(game_object);

    return game_object;
}

GameObject* ModuleSceneIntro::CreateSavedGameObject(GameObject* parent, const char* name)
{
    GameObject* game_object = new GameObject(parent, name);
    saved_scene_game_object.push_back(game_object);

    return game_object;
}




