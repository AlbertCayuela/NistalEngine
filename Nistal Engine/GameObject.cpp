#include "Application.h"
#include "GameObject.h"
#include "GOMaterial.h"
#include "GOMesh.h"
#include "GOTransform.h"
#include "GOCamera.h"
#include "GOAudioSource.h"
#include "GOAudioListener.h"

GameObject::GameObject(GameObject* parent, const char* name)
{
	this->parent = parent;

	if (parent != nullptr) 
	{
		parent->children.push_back(this);
		parent_uuid = parent->uuid;
	}
	else if (parent == nullptr)
	{
		parent_uuid = 0;
	}

	uuid = GenerateUUID();

	if(name != nullptr)
		GetNames(name);

	AddComponent(GOCOMPONENT_TYPE::TRANSFORM, "transform");

	LOG("New GameObject created: %s", this->name.c_str());
	LOG("GameObject UUID: %u", uuid);
	LOG("GameObject parent UUID: %u", parent_uuid);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
	if (mesh != nullptr && !has_bbox)
	{
		AddBoundingBox();
		has_bbox = true;
		LOG("Added bounding box to %s", name.c_str());
	}

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(dt);
	}

	if (camera != nullptr)
		camera->Update(dt);


	if (!App->scene_intro->playing) 
	{
		DrawBoundingBox();
	}
}

GOComponent* GameObject::AddComponent(GOCOMPONENT_TYPE type, const char* name)
{
	GOComponent* component = nullptr;

	switch (type)
	{
	case(GOCOMPONENT_TYPE::MATERIAL):
		material = new GOMaterial(this, name);
		component = material;
		has_material = true;
		break;
	case(GOCOMPONENT_TYPE::MESH):
		mesh = new GOMesh(this, name);
		component = mesh;
		has_mesh = true;
		break;
	case(GOCOMPONENT_TYPE::TRANSFORM):
		transform = new GOTransform(this, name);
		component = transform;
		break;
	case(GOCOMPONENT_TYPE::CAMERA):
		camera = new GOCamera(this);
		component = camera;
		has_camera = true;
		break;
	case(GOCOMPONENT_TYPE::AUDIO_SOURCE):
		audio_source = new GOAudioSource(this);
		component = audio_source;
		has_audio_source = true;
		break;
	case(GOCOMPONENT_TYPE::AUDIO_LISTENER):
		audio_listener = new GOAudioListener(this);
		component = audio_listener;
		has_audio_listener = true;
		break;
	default:
		break;
	}

	go_components.push_back(component);

	return component;
}

GOComponent* GameObject::GetComponent(GOCOMPONENT_TYPE type)
{
	return nullptr;
}

void GameObject::GetNames(const char* name)
{
	path = name;
	this->name = path.substr(path.find_last_of("/\\") + 1);
	std::string::size_type const p(this->name.find_last_of('.'));
	ui_name = this->name.substr(0, p);
}

u32 GameObject::GenerateUUID()
{
	return lcg.Int();
}

void GameObject::AddBoundingBox()
{
	bbox.SetNegativeInfinity();

	if (mesh != nullptr)
	{
		bbox.Enclose((float3*)mesh->mesh_info.vertices, mesh->mesh_info.num_vertex);
		obb_box.SetFrom(bbox);
		obb_box.Transform(transform->GlobalMatrix());
		if (obb_box.IsFinite())
			bbox = obb_box.MinimalEnclosingAABB();
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
		(*i)->AddBoundingBox();
}

void GameObject::DrawBoundingBox()
{

	glBegin(GL_LINES);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	for (uint i = 0; i < bbox.NumEdges(); i++) 
	{
		glVertex3f(bbox.Edge(i).a.x, bbox.Edge(i).a.y, bbox.Edge(i).a.z);
		glVertex3f(bbox.Edge(i).b.x, bbox.Edge(i).b.y, bbox.Edge(i).b.z);
	}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
		(*i)->DrawBoundingBox();

}

void GameObject::DeleteGameObjects()
{
	App->scene_intro->game_objects.clear();
	children.clear();
	go_components.clear();
}

void GameObject::SaveInfoGameObject(GameObject* go, JSON_Array* json_array)
{
	//BASIC INFO
	JSON_Value* value_json = json_value_init_object();
	JSON_Object* object_json = json_value_get_object(value_json);

	json_object_set_string(object_json, "Name:", go->name.c_str());
	json_object_set_number(object_json, "UUID", go->uuid);
	json_object_set_number(object_json, "Parent UUID", go->parent_uuid);

		//COMPONENTS INFO
	components = json_value_init_array();
	componentsObj = json_value_get_array(components);

	if (go->transform != nullptr)
		go->transform->SaveSceneTransform(componentsObj, go);

	if (go->mesh != nullptr)
		go->mesh->SaveSceneMesh(componentsObj, go);

	if (go->material != nullptr)
		go->material->SaveSceneMaterial(componentsObj);

	if (go->camera != nullptr)
		go->camera->SaveSceneCamera(componentsObj);

	json_object_set_value(object_json, "Components:", components);

	json_array_append_value(json_array, value_json);
}

void GameObject::LoadInfoGameObject(GameObject* game_object, JSON_Object* obj)
{
	game_object->GetNames(json_object_get_string(obj, "Name:"));
	game_object->uuid = json_object_get_number(obj, "UUID");
	game_object->parent_uuid = json_object_get_number(obj, "Parent UUID");

	JSON_Array* Array = json_object_get_array(obj, "Components:");
	JSON_Object* type;
	int size = json_array_get_count(Array);

	for (int i = 0; i < size; i++)
	{
		type = json_array_get_object(Array, i);
		int num_type = json_object_get_number(type, "Type:");

		if (num_type == 1)
		{
			game_object->transform->LoadSceneTransform(type);
		}
		if (num_type == 2)
		{
			game_object->AddComponent(GOCOMPONENT_TYPE::MESH, "mesh");
			game_object->mesh->LoadSceneMesh(type, game_object);
		}
		if (num_type == 3) 
		{
			game_object->AddComponent(GOCOMPONENT_TYPE::MATERIAL, "material");
			game_object->material->LoadSceneMaterial(type, game_object);
		}
		if (num_type == 4)
		{
			game_object->AddComponent(GOCOMPONENT_TYPE::CAMERA, "camera");
			game_object->camera->LoadSceneCamera(type, game_object);
		}
	}
	//uuid = json_object_get_number(obj, "UID:");

	LOG("Loading object info:");
	LOG("NAME: %s", ui_name.c_str());
	LOG("uuid: %i", uuid);
	LOG("parent uuid: %i", parent_uuid);
}