#ifndef __GOCAMERA_H__
#define __GOCAMERA_H__

#include "GOComponent.h"
#include "Globals.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

class GOCamera : public GOComponent
{
public:

	GOCamera(GameObject* parent);
	~GOCamera();

};

#endif
