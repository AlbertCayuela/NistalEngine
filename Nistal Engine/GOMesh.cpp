#include "GOMesh.h"
#include "GOMaterial.h"
#include "Application.h"

GOMesh::GOMesh(GameObject* game_object, const char* name) : GOComponent(game_object)
{
    this->name = name;
	LOG("Mesh added to gameobject: %s", game_object->name.c_str());
}

GOMesh::~GOMesh()
{
}

void GOMesh::DrawMesh(uint texture_id)
{
    if (parent->active)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        if (parent->has_material)
        {
            //bind texture
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id);
        }

        //bind vertices
        glBindBuffer(GL_ARRAY_BUFFER, mesh_info.id_vertex);
        glVertexPointer(3, GL_FLOAT, 0, NULL);

        //bind uvs
        glBindBuffer(GL_ARRAY_BUFFER, mesh_info.id_uvs);
        glTexCoordPointer(2, GL_FLOAT, 0, NULL);

        //bind indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_info.id_index);

        //Draw
        glDrawElements(GL_TRIANGLES, mesh_info.num_index, GL_UNSIGNED_INT, NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
}

void GOMesh::SetMesh(const char* path)
{
    App->load_fbx->LoadFBX(path);
}
