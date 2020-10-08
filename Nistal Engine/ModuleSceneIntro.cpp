#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"


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

    Cube testWireframe(1.0f, 1.0f, 1.0f);
    testWireframe.SetPos(0.0f, 0.5f, 0.0f);
    testWireframe.color = Yellow;
    testWireframe.wire = true;
    testWireframe.Render();


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

