#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
struct PhysBody3D;
struct PhysMotor3D;
using namespace std;

class GameObject;

class ModuleSceneIntro : public Module
{
public:
    ModuleSceneIntro(Application* app, bool start_enabled = true);
    ~ModuleSceneIntro();

    bool Start();
    update_status PreUpdate(float dt);
    update_status Update(float dt);
    update_status PostUpdate(float dt);
    bool CleanUp();

    GameObject* CreateGameObject(GameObject* parent, const char* name);
    GameObject* CreateOWNGameObject(GameObject* parent, const char* name);

    vector<GameObject*> game_objects;
    vector<GameObject*> own_game_objects;
    GameObject* root = nullptr;
    GameObject* camera = nullptr;
    GameObject* street = nullptr;
    GameObject* selected_go = nullptr;

    bool render_street = false;
    bool render_own_model = false;
};