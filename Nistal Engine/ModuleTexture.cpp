#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleLoadFBX.h"
#include "cubeEngine.h"

#include "Devil/include/il.h"
#include "Devil/include/ilu.h"
#include "Devil/include/ilut.h"

#include "Assimp/include/material.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Start()
{
    texture_node = json_object_dotget_object(App->config, "Texture");
    texture_path = json_object_get_string(texture_node, "Texture Path");

    ////TEXTURES
    //GLubyte HouseImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
    //for (int i = 0; i < CHECKERS_HEIGHT; i++) {
    //    for (int j = 0; j < CHECKERS_WIDTH; j++) {
    //        int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
    //        HouseImage[i][j][0] = (GLubyte)c;
    //        HouseImage[i][j][1] = (GLubyte)c;
    //        HouseImage[i][j][2] = (GLubyte)c;
    //        HouseImage[i][j][3] = (GLubyte)255;
    //    }
    //}

    LoadTexture(App->load_fbx->model, texture_path);

    bool testing = ilLoadImage(texture_path);
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    //ilutRenderer(ILUT_OPENGL);

    App->load_fbx->model.texture = ilutGLBindTexImage(); //this line changes the color environment to 1 pixel color of Lenna

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

    //LOG("TODO: Load Texture :)");
    ////glTexImage2D(GL_TEXTURE_2D, App->load_fbx->LOD, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0 /*this value must be 0 xD*/, GL_RGBA, GL_UNSIGNED_BYTE, HouseImage);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //color = white

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glGenTextures(1, &App->load_fbx->model.texture);
    ////glBindTexture(GL_TEXTURE_2D, texture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
    //    0, GL_RGBA, GL_UNSIGNED_BYTE, HouseImage);

    //glBindTexture(GL_TEXTURE_2D, 0);

    return ret;
}


void ModuleTexture::LoadUVs(modelData* model, aiMesh* mesh)
{
    //has_data means nothing in our code :)
    //buffer size means id
    //buffer means uvs

    //has data true

    model->num_uvs = model->num_vertex;

    model->id_uvs = model->num_uvs_channels * model->num_uvs * 2;
    model->uvs = new float[model->id_uvs];

    model->channel_buffer_size = model->num_uvs * 2;
    for (uint channel = 0; channel < model->num_uvs_channels; ++channel)
    {
        if (mesh->HasTextureCoords(channel))
        {
            if (mesh->mNumUVComponents[channel] == 2)
            {
                for (uint j = 0; j < model->num_uvs; ++j)
                {
                    memcpy(&model->uvs[(channel * model->channel_buffer_size) + j * 2], &mesh->mTextureCoords[channel][j], sizeof(float) * 2);
                }
            
            }
            else {
                memset(&model->uvs[channel * model->channel_buffer_size], 0, sizeof(float) * model->channel_buffer_size);
            }
        }
    }

}

void ModuleTexture::LoadMaterials(const aiScene* scene, aiMesh* mesh, modelData* model)
{
    model->has_texture = true;
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE); //only load DIFFUSE textures.

    if (numTextures > 0)
    {
        bool testing = ilLoadImage(texture_path);
        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        //ilutRenderer(ILUT_OPENGL);

        if (testing) {
            LOG("Texture loaded through path");
            
            model->texture = ilutGLBindTexImage(); //this line changes the color environment to 1 pixel color of Lenna
            glBindTexture(GL_TEXTURE_2D, model->texture);

        }
        else {
            LOG("Loading error in texture path");
        }
    }
}