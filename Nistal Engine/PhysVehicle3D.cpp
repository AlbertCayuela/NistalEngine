#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Color.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	//Car Parts
	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	chassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);

	Cube core(info.core.x, info.core.y, info.core.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&core.transform);

	Cube wall1_car(info.wall1_car.x, info.wall1_car.y, info.wall1_car.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&wall1_car.transform);

	Cube wall2_car(info.wall2_car.x, info.wall2_car.y, info.wall2_car.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&wall2_car.transform);

	Cube wall3_car(info.wall3_car.x, info.wall3_car.y, info.wall3_car.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&wall3_car.transform);

	Cube wall4_car(info.wall4_car.x, info.wall4_car.y, info.wall4_car.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&wall4_car.transform);

	Cube front(info.front.x, info.front.y, info.front.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front.transform);

	//Rotation Quaternion
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	
	//Offset
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	btVector3 floor_offset(info.core_offset.x, info.core_offset.y, info.core_offset.z);
	floor_offset = floor_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 wall1_car_offset(info.wall1_car_offset.x, info.wall1_car_offset.y, info.wall1_car_offset.z);
	wall1_car_offset = wall1_car_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 wall2_car_offset(info.wall2_car_offset.x, info.wall2_car_offset.y, info.wall2_car_offset.z);
	wall2_car_offset = wall2_car_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 wall3_car_offset(info.wall3_car_offset.x, info.wall3_car_offset.y, info.wall3_car_offset.z);
	wall3_car_offset = wall3_car_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 wall4_car_offset(info.wall4_car_offset.x, info.wall4_car_offset.y, info.wall4_car_offset.z);
	wall4_car_offset = wall4_car_offset.rotate(q.getAxis(), q.getAngle());

	btVector3 front_offset(info.front_offset.x, info.front_offset.y, info.front_offset.z);
	front_offset = front_offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	core.transform.M[12] += floor_offset.getX();
	core.transform.M[13] += floor_offset.getY();
	core.transform.M[14] += floor_offset.getZ();

	wall1_car.transform.M[12] += wall1_car_offset.getX();
	wall1_car.transform.M[13] += wall1_car_offset.getY();
	wall1_car.transform.M[14] += wall1_car_offset.getZ();

	wall2_car.transform.M[12] += wall2_car_offset.getX();
	wall2_car.transform.M[13] += wall2_car_offset.getY();
	wall2_car.transform.M[14] += wall2_car_offset.getZ();

	wall3_car.transform.M[12] += wall3_car_offset.getX();
	wall3_car.transform.M[13] += wall3_car_offset.getY();
	wall3_car.transform.M[14] += wall3_car_offset.getZ();

	wall4_car.transform.M[12] += wall4_car_offset.getX();
	wall4_car.transform.M[13] += wall4_car_offset.getY();
	wall4_car.transform.M[14] += wall4_car_offset.getZ();

	front.transform.M[12] += front_offset.getX();
	front.transform.M[13] += front_offset.getY();
	front.transform.M[14] += front_offset.getZ();

	//Render
	chassis.Render();
	core.Render();
	wall1_car.Render();
	wall2_car.Render();
	wall3_car.Render();
	wall4_car.Render();
	front.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

vec3 PhysVehicle3D::GetBackDirection() const
{
	btVector3 ForwardVector = vehicle->getForwardVector();
	vec3 BackDirection = { -ForwardVector.getX(), -ForwardVector.getY(), -ForwardVector.getZ() };
	return BackDirection;
}