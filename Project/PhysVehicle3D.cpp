#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Application.h"
#include "ModulePlayer.h"
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

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	if (restart)
	{
		restart = false;
		SetPos(0, 61, 10);
		vehicle->resetSuspension();
		body->setAngularVelocity({ 0,0,0 });
		body->setLinearVelocity({ 0,0,0 });

		btQuaternion q1 = vehicle->getChassisWorldTransform().getRotation();
		btQuaternion q2 = startQuat - q1;
		offset = offset.rotate(q2.getAxis(), q2.getAngle());

		chassis.transform.M[12] += offset.getX();
		chassis.transform.M[13] += offset.getY();
		chassis.transform.M[14] += offset.getZ();

	}
	

	Cube secondChassis(info.secondChassis_size.x, info.secondChassis_size.y, info.secondChassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&secondChassis.transform);
	btVector3 secondOffset(info.secondChassis_offset.x, info.secondChassis_offset.y, info.secondChassis_offset.z);
	secondOffset = secondOffset.rotate(q.getAxis(), q.getAngle());
	secondChassis.color.Set(0.50f, 0.39f, 0.52f,1.0f);

	secondChassis.transform.M[12] += secondOffset.getX();
	secondChassis.transform.M[13] += secondOffset.getY();
	secondChassis.transform.M[14] += secondOffset.getZ();

	chassis.Render();
	secondChassis.Render();
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