#include "Application.h"
#include "GOTransform.h"
#include "GOCamera.h"
#include "ModuleFS.h"

GOTransform::GOTransform(GameObject* game_object, const char* name):GOComponent(game_object)
{
	this->name = name;
	this->type = GOCOMPONENT_TYPE::TRANSFORM;
}

GOTransform::~GOTransform()
{
	if (parent != nullptr) 
	{
		parent->transform = nullptr;
	}
}

math::float4x4& GOTransform::LocalMatrix() const
{
	return float4x4::FromTRS(position, rotation, scale);
}

math::float4x4 GOTransform::GlobalMatrix() const
{
	float4x4 local_matrix = LocalMatrix();
	if (parent->parent != nullptr)
	{
		float4x4 global_matrix = parent->parent->transform->GlobalMatrix() * local_matrix;
		return global_matrix;
	}
	else
	{
		return local_matrix;
	}
}

void GOTransform::NewPosition(float3 new_position)
{
	position = new_position;

	if (parent->has_camera)
		parent->camera->frustum.pos = position;

}

void GOTransform::NewRotation(float3 new_rotation)
{
	rotation = Quat::FromEulerXYZ(new_rotation.x * DEGTORAD, new_rotation.y * DEGTORAD, new_rotation.z * DEGTORAD);
}

void GOTransform::NewScale(float3 new_scale)
{
	scale = new_scale;
}

void GOTransform::NewMatrix(float4x4& global_matrix)
{
	float4x4 mat;

	if (parent->parent != nullptr) 
	{
		float4x4 parent_mat = parent->parent->transform->GlobalMatrix().Inverted();
		mat = parent_mat * global_matrix;
	}
	else 
	{
		mat = global_matrix;
	}

	transform_matrix.Set(GlobalMatrix());
	mat.Decompose(position, rotation, scale);
}

void GOTransform::SaveSceneTransform(JSON_Array* componentsObj, GameObject* game_object)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);

	float3 save_rot = this->rotation.ToEulerXYZ() * RADTODEG;

	json_object_set_number(componentObj, "Type:", this->type);
	json_object_set_number(componentObj, "PositionX", position.x);
	json_object_set_number(componentObj, "PositionY", position.y);
	json_object_set_number(componentObj, "PositionZ", position.z);
	json_object_set_number(componentObj, "RotationX", save_rot.x);
	json_object_set_number(componentObj, "RotationY", save_rot.y);
	json_object_set_number(componentObj, "RotationZ", save_rot.z);
	json_object_set_number(componentObj, "ScaleX", scale.x);
	json_object_set_number(componentObj, "ScaleY", scale.x);
	json_object_set_number(componentObj, "ScaleZ", scale.x);

	json_array_append_value(componentsObj, component);
}

void GOTransform::LoadSceneTransform(JSON_Object* obj)
{
	float3 load_rot;

	position.x = json_object_get_number(obj, "PositionX");
	position.y = json_object_get_number(obj, "PositionY");
	position.z = json_object_get_number(obj, "PositionZ");
	load_rot.x = json_object_get_number(obj, "RotationX");
	load_rot.y = json_object_get_number(obj, "RotationY");
	load_rot.z = json_object_get_number(obj, "RotationZ");
	scale.x = json_object_get_number(obj, "ScaleX");
	scale.y = json_object_get_number(obj, "ScaleY");
	scale.z = json_object_get_number(obj, "ScaleZ");

	rotation = Quat::FromEulerXYZ(load_rot.x * DEGTORAD, load_rot.y * DEGTORAD, load_rot.z * DEGTORAD);
}
