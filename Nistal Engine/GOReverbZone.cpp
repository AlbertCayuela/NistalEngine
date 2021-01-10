#include "GOReverbZone.h"
#include "Application.h"
#include "GOAudioSource.h"
#include "GOTransform.h"

GOReverbZone::GOReverbZone(GameObject* game_object) : GOComponent(game_object)
{
	this->type = GOCOMPONENT_TYPE::REVERB_ZONE;
}

GOReverbZone::~GOReverbZone()
{
}

void GOReverbZone::Update(float dt)
{
	ZoneSphere();

	if (!App->scene_intro->playing) 
	{
		DrawZone();
	}
	for (int i = 0; i < App->scene_intro->game_objects.size(); i++)
	{
		GOAudioSource* aux = App->scene_intro->game_objects[i]->audio_source;

		if (aux != nullptr) 
		{
			if (reverb_sphere.Intersects(App->scene_intro->game_objects[i]->bbox))
			{
				//LOG("si");
				aux->source->ApplyEnvReverb(1.0f, "enable_reverb");
			}
			else
			{
				//LOG("NO");
				aux->source->ApplyEnvReverb(0, "enable_reverb");
			}
		}
	}
}

void GOReverbZone::ZoneSphere()
{
	reverb_sphere.pos = parent->transform->position;
	box = reverb_sphere.MinimalEnclosingAABB();
	math::OBB bounding_box(box);
	box.Transform(parent->transform->transform_matrix);
}

void GOReverbZone::NewRadius(float new_radius)
{
	reverb_radius = new_radius;
}

void GOReverbZone::DrawZone()
{
	glLineWidth(1.0f);
	glColor3f(2.0f, 2.0f, 2.0f);

	float degtorad = (360 / 12) * DEGTORAD;

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 12; i++)
	{
		glVertex3f(cos(degtorad * i) * reverb_radius + reverb_sphere.pos.x, reverb_sphere.pos.y, sin(degtorad * i) * reverb_radius + reverb_sphere.pos.z);
	}

	glEnd();
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 12; i++) 
	{
		glVertex3f(cos(degtorad * i) * reverb_radius + reverb_sphere.pos.x, sin(degtorad * i) * reverb_radius + reverb_sphere.pos.y, reverb_sphere.pos.z);
	}

	glEnd();
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 12; i++)
	{
		glVertex3f(reverb_sphere.pos.x, sin(degtorad * i) * reverb_radius + reverb_sphere.pos.y, cos(degtorad * i) * reverb_radius + reverb_sphere.pos.z);
	}

	glEnd();

	glLineWidth(1.0f);
}


void GOReverbZone::SaveSceneReverbZone(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);

	json_object_set_number(componentObj, "Type:", this->type);
	json_object_set_number(componentObj, "Radius", reverb_radius);

	json_array_append_value(componentsObj, component);
}

void GOReverbZone::LoadSceneReverbZone(JSON_Object* obj, GameObject* game_object)
{
	game_object->reverb_zone->reverb_radius = json_object_get_number(obj, "Radius");
}



