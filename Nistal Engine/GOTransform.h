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
	math::float4x4 GlobalMatrix() const;

	void NewPosition(float3 new_position);
	void NewRotation(float3 new_rotation);
	void NewScale(float3 new_scale);
	void NewMatrix(float4x4& global_matrix);

	//JSON data saving
	void SaveSceneTransform(JSON_Array* componentsObj, GameObject* game_object);
	void LoadSceneTransform(JSON_Object* obj);

public:

	float4x4 local_matrix = math::float4x4::identity;
	float4x4 global_matrix = math::float4x4::identity;
	float4x4 transform_matrix = math::float4x4::identity;

	float3 position = math::float3::zero;
	Quat rotation = math::Quat::identity;
	float3 scale = math::float3::one;

	std::string name;
};

#endif
