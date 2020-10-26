#ifndef __GOTRANSFORM_H__
#define __GOTRANSFORM_H__

#include "GOComponent.h"

#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "MathGeoLib/include/Math/float4x4.h"

class GOTransform : public GOComponent 
{

public:

	GOTransform(GameObject* parent);
	~GOTransform();

public:

	float4x4 transform_matrix;

	float3 position;
	Quat rotation;
	float3 scale;
};

#endif
