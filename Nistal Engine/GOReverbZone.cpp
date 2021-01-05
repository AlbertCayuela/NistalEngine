#include "GOReverbZone.h"
#include "Application.h"
#include "GOAudioSource.h"
#include "GOTransform.h"

GOReverbZone::GOReverbZone(GameObject* game_object) : GOComponent(game_object)
{
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

	for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i != App->scene_intro->game_objects.end(); ++i)
	{
		GOAudioSource* aux = (*i)->audio_source;
		if (aux != nullptr) 
		{
			aux->source->ApplyEnvReverb(12, "reverb");
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




