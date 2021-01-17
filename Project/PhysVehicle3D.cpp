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

    Cube aleronChassis(info.aleronChassis_size.x, info.aleronChassis_size.y, info.aleronChassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&aleronChassis.transform);
	btVector3 aleronOffset(info.aleronChassis_offset.x, info.aleronChassis_offset.y, info.aleronChassis_offset.z);
	aleronOffset = aleronOffset.rotate(q.getAxis(), q.getAngle());
	aleronChassis.color.Set(0.50f, 0.39f, 0.52f,1.0f);

	aleronChassis.transform.M[12] += aleronOffset.getX();
	aleronChassis.transform.M[13] += aleronOffset.getY();
	aleronChassis.transform.M[14] += aleronOffset.getZ();

	Cube lateralRChassis(info.lateralRChassis_size.x, info.lateralRChassis_size.y, info.lateralRChassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lateralRChassis.transform);
	btVector3 lateralROffset(info.lateralRChassis_offset.x, info.lateralRChassis_offset.y, info.lateralRChassis_offset.z);
	lateralROffset = lateralROffset.rotate(q.getAxis(), q.getAngle());
	lateralRChassis.color.Set(0.50f, 0.39f, 0.52f, 1.0f);

	lateralRChassis.transform.M[12] += lateralROffset.getX();
	lateralRChassis.transform.M[13] += lateralROffset.getY();
	lateralRChassis.transform.M[14] += lateralROffset.getZ();

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

		aleronOffset = aleronOffset.rotate(q.getAxis(), q.getAngle());

		aleronChassis.transform.M[12] += aleronOffset.getX();
		aleronChassis.transform.M[13] += aleronOffset.getY();
		aleronChassis.transform.M[14] += aleronOffset.getZ();

		lateralROffset = lateralROffset.rotate(q.getAxis(), q.getAngle());

		lateralRChassis.transform.M[12] += lateralROffset.getX();
		lateralRChassis.transform.M[13] += lateralROffset.getY();
		lateralRChassis.transform.M[14] += lateralROffset.getZ();

	}
	//Render del chassis parte por parte
	chassis.Render();
	aleronChassis.Render();
	lateralRChassis.Render();
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