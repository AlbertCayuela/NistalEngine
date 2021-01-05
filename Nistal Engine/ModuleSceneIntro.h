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

    vector<GameObject*> game_objects;
    vector<GameObject*> own_game_objects;
    vector<GameObject*> saved_scene_game_object;

    GameObject* root = nullptr;
    GameObject* camera = nullptr;
    GameObject* selected_go = nullptr;
    GameObject* sound_go = nullptr;
    GameObject* moving_sound_go = nullptr;
    //GameObject* listener_go = nullptr;
    GameObject* reverb_zone_go = nullptr;

    bool playing = false;
    bool paused = false;
    bool render_street = false;
    bool objects_created = false;
};