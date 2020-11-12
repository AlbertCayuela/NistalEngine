#include "GOTransform.h"


GOTransform::GOTransform(GameObject* game_object, const char* name):GOComponent(game_object)
{
	this->name = name;

}

GOTransform::~GOTransform()
{
}

math::float4x4& GOTransform::LocalMatrix() const
{
	return float4x4::FromTRS(position, rotation, scale);
}

math::float4x4& GOTransform::GlobalMatrix() const
{
	float4x4 local_matrix = LocalMatrix();
	if (parent->parent != nullptr)
	{
		float4x4 global_matrix = (parent->parent->transform->GlobalMatrix()) * local_matrix;
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
}
