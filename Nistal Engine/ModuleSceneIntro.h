#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "ImGui/imconfig.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLibFwd.h"

#include "Assimp/include/cimport.h"

struct PhysBody3D;
struct PhysMotor3D;

struct vertexData {

    uint id_index = 0; //index in VRAM
    uint num_index = 0;
    uint* index = nullptr;

    uint id_vertx = 0; //unique vertex in VRAM
    uint num_vertex = 0;
    float* vertex = nullptr;
};

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

    void DrawCubeDirectMode();
    void DrawCubeVertexArray();
    void DrawCubeIndices();

public:
    vertexData data;
};