#include "Application.h"
#include "GameObject.h"
#include "GOMaterial.h"
#include "GOMesh.h"
#include "GOTransform.h"
#include "GOCamera.h"

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

	DrawBoundingBox();
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

void GameObject::SaveInfoGameObject(GameObject* go, JSON_Array* json_array)
{
	//BASIC INFO
	JSON_Value* value_json = json_value_init_object();
	JSON_Object* object_json = json_value_get_object(value_json);

	json_object_set_string(object_json, "Name:", go->name.c_str());
	/*json_object_set_number(object_json, "UUID:", go->uuid);
	if (go->parent != nullptr)
		json_object_set_number(object_json, "Parent UUID:", go->parent->uuid);*/

		//COMPONENTS INFO
	JSON_Value* components = json_value_init_array();
	JSON_Array* componentsObj = json_value_get_array(components);

	if (go->transform != nullptr)
		go->transform->JsonSaveTransform(componentsObj, go);

	json_object_set_value(object_json, "Components:", components);

	json_array_append_value(json_array, value_json);
}
