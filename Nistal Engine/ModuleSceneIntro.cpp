#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

//#include "ImGui/imconfig.h"
//#include "ImGui/imgui.h"
//#include "ImGui/imgui_impl_sdl.h"
//#include "ImGui/imgui_impl_opengl3.h"
//#include "Glew/include/glew.h"
//
//#include "SDL/include/SDL.h"
//#include "SDL/include/SDL_opengl.h"
//
//#pragma comment (lib, "Glew/lib/glew32.lib")
//#ifdef NDEBUG
//#pragma comment (lib, "MathGeoLib/libx86/Release/MathGeoLib.lib") 
//#else
//#pragma comment (lib, "MathGeoLib/libx86/Debug/MathGeoLib.lib") 
//#endif


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

    //App->camera->Move(vec3(0.0f, 0.0f, 0.0f));
    App->camera->LookAt(vec3(0, 0, 0));

    //glewInit();
    //ImGui::CreateContext();
    //ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    //ImGui_ImplOpenGL3_Init();
    //ImGui::StyleColorsDark();

    return ret;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplSDL2_NewFrame(App->window->window);
    //ImGui::NewFrame();

    //ImGui::ShowDemoWindow(&show_window);

    return UPDATE_CONTINUE;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{    
    PlanePrimitive p(0, 1, 0, 0);
    p.axis = true;
    p.Render();

    //CLOSING WINDOW

    //math::Sphere x({ 0,0,0 }, 4);
    //math::Sphere y({ 0,0,0 }, 7);

    //if (x.Intersects(y))
    //    LOG("BEEP BEEP!!");
    //
    //ImGui::Text("Closing Window");
    //if (ImGui::Button("Exit"))
    //{
    //    return UPDATE_STOP;
    //}


    return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
    LOG("Unloading Intro scene");

 /*   ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(App->renderer3D->context);
    SDL_DestroyWindow(App->window->window);
    SDL_Quit();*/

    return true;
}

