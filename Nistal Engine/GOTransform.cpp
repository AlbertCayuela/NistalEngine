#include "GOTransform.h"

GOTransform::GOTransform(GameObject* game_object, const char* name):GOComponent(game_object)
{
	this->name = name;

}

GOTransform::~GOTransform()
{
}

//math::float4x4& GOTransform::LocalMatrix() const
//{
//	return float4x4::FromTRS(position, rotation, scale);
//}

//math::float4x4& GOTransform::GlobalMatrix() const
//{
//
//}
