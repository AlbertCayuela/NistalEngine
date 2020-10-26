#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleLoadFBX.h"

#include "Devil/include/il.h"
#include "Devil/include/ilu.h"
#include "Devil/include/ilut.h"

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Start()
{
    texture_node = json_object_dotget_object(App->config, "Texture");
    texture_path = json_object_get_string(texture_node, "Texture Path");

    //TEXTURES
    GLubyte HouseImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
    for (int i = 0; i < CHECKERS_HEIGHT; i++) {
        for (int j = 0; j < CHECKERS_WIDTH; j++) {
            int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
            HouseImage[i][j][0] = (GLubyte)c;
            HouseImage[i][j][1] = (GLubyte)c;
            HouseImage[i][j][2] = (GLubyte)c;
            HouseImage[i][j][3] = (GLubyte)255;
        }
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &App->load_fbx->texture);
    glBindTexture(GL_TEXTURE_2D, App->load_fbx->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
        0, GL_RGBA, GL_UNSIGNED_BYTE, HouseImage);


    bool testing = ilLoadImage(texture_path);
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    //ilutRenderer(ILUT_OPENGL);

    App->load_fbx->texture = ilutGLBindTexImage(); //this line changes the color environment to 1 pixel color of Lenna

    if (testing) {
        LOG("Texture loaded through path");
    }
    else {
        LOG("Loading error in texture path");
        return false;
    }

	return true;
}

update_status ModuleTexture::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	return true;
}

bool ModuleTexture::LoadTexture(modelData model, const char* path)
{
    bool ret = true;

    LOG("TODO: Load Texture :)");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &App->load_fbx->texture);
    glBindTexture(GL_TEXTURE_2D, App->load_fbx->texture);

    //TODO: Observe what happens if we change GL_REPEAT for GL_MIRRORED_REPEAT or GL_CLAMP or GL_CLAMP_TO_BORDER, hmm
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, App->load_fbx->LOD, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0 /*this value must be 0 xD*/, GL_RGBA, GL_UNSIGNED_BYTE, App->load_fbx->checkerImage);

    glBindTexture(GL_TEXTURE_2D, 0);

    return ret;
}

void ModuleTexture::DrawTexture()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //color white
    glBindTexture(GL_TEXTURE_2D, App->load_fbx->texture);
    App->scene_intro->my_cube.DrawCubeDirectMode();
    glDisable(GL_TEXTURE_2D);
}