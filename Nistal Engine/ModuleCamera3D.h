#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "MathGeoLib/include/Math/float3.h"
#include <map>

class GameObject;
class GOCamera;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3 &Movement);

	void TestAABBIntersection(LineSegment ray, GameObject* game_object, map<GameObject*, float> &intersected_objects);
	bool TestTriIntersection(LineSegment ray, GameObject *& game_object, map<GameObject*, float>& intersected_objects); 
	void DebugPickingRay(LineSegment ray);

	GOCamera* GetCurrentCamera() const;

private:

	void FocusOnTarget(const float3& focus,const float& distance);
	void RotateAroundTarget();

public:
	
	GOCamera* camera = nullptr;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;

};