#ifndef __GOTRANSFORM_H__
#define __GOTRANSFORM_H__

#include "GOComponent.h"

#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "MathGeoLib/include/Math/float4x4.h"

class GOTransform : public GOComponent 
{

public:

	GOTransform(GameObject* game_object, const char* name);
	~GOTransform();

	math::float4x4& LocalMatrix() const;
	math::float4x4& GlobalMatrix() const;

public:

	float4x4 transform_matrix = math::float4x4::identity;

	float3 position = math::float3::zero;
	Quat rotation = math::Quat::identity;
	float3 scale = math::float3::one;

	std::string name;
};

#endif
