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

	Cube lateralLChassis(info.lateralLChassis_size.x, info.lateralLChassis_size.y, info.lateralLChassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lateralLChassis.transform);
	btVector3 lateralLOffset(info.lateralLChassis_offset.x, info.lateralLChassis_offset.y, info.lateralLChassis_offset.z);
	lateralLOffset = lateralLOffset.rotate(q.getAxis(), q.getAngle());
	lateralLChassis.color.Set(0.50f, 0.39f, 0.52f, 1.0f);

	lateralLChassis.transform.M[12] += lateralLOffset.getX();
	lateralLChassis.transform.M[13] += lateralLOffset.getY();
	lateralLChassis.transform.M[14] += lateralLOffset.getZ();

	Cube lateralR1Chassis(info.lateralR1Chassis_size.x, info.lateralR1Chassis_size.y, info.lateralR1Chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lateralR1Chassis.transform);
	btVector3 lateralR1Offset(info.lateralR1Chassis_offset.x, info.lateralR1Chassis_offset.y, info.lateralR1Chassis_offset.z);
	lateralR1Offset = lateralR1Offset.rotate(q.getAxis(), q.getAngle());
	lateralR1Chassis.color.Set(0.50f, 0.39f, 0.52f, 1.0f);

	lateralR1Chassis.transform.M[12] += lateralR1Offset.getX();
	lateralR1Chassis.transform.M[13] += lateralR1Offset.getY();
	lateralR1Chassis.transform.M[14] += lateralR1Offset.getZ();

	Cube lateralL1Chassis(info.lateralL1Chassis_size.x, info.lateralL1Chassis_size.y, info.lateralL1Chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lateralL1Chassis.transform);
	btVector3 lateralL1Offset(info.lateralL1Chassis_offset.x, info.lateralL1Chassis_offset.y, info.lateralL1Chassis_offset.z);
	lateralL1Offset = lateralL1Offset.rotate(q.getAxis(), q.getAngle());
	lateralL1Chassis.color.Set(0.50f, 0.39f, 0.52f, 1.0f);

	lateralL1Chassis.transform.M[12] += lateralL1Offset.getX();
	lateralL1Chassis.transform.M[13] += lateralL1Offset.getY();
	lateralL1Chassis.transform.M[14] += lateralL1Offset.getZ();

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

		lateralLOffset = lateralROffset.rotate(q.getAxis(), q.getAngle());

		lateralLChassis.transform.M[12] += lateralLOffset.getX();
		lateralLChassis.transform.M[13] += lateralLOffset.getY();
		lateralLChassis.transform.M[14] += lateralLOffset.getZ();

		lateralR1Offset = lateralR1Offset.rotate(q.getAxis(), q.getAngle());

		lateralR1Chassis.transform.M[12] += lateralR1Offset.getX();
		lateralR1Chassis.transform.M[13] += lateralR1Offset.getY();
		lateralR1Chassis.transform.M[14] += lateralR1Offset.getZ();

		lateralL1Offset = lateralROffset.rotate(q.getAxis(), q.getAngle());

		lateralL1Chassis.transform.M[12] += lateralL1Offset.getX();
		lateralL1Chassis.transform.M[13] += lateralL1Offset.getY();
		lateralL1Chassis.transform.M[14] += lateralL1Offset.getZ();

	}
	//Render del chassis parte por parte
	chassis.Render();
	aleronChassis.Render();
	lateralRChassis.Render();
	lateralLChassis.Render();
	lateralR1Chassis.Render();
	lateralL1Chassis.Render();
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