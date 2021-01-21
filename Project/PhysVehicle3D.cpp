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

	Cube cabinChassis(info.cabinChassis_size.x, info.cabinChassis_size.y, info.cabinChassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&cabinChassis.transform);
	btVector3 cabinOffset(info.cabinChassis_offset.x, info.cabinChassis_offset.y, info.cabinChassis_offset.z);
	cabinOffset = cabinOffset.rotate(q.getAxis(), q.getAngle());
	cabinChassis.color.Set(2.224f, 2.220f, 0.f, 1.f);

	cabinChassis.transform.M[12] += cabinOffset.getX();
	cabinChassis.transform.M[13] += cabinOffset.getY();
	cabinChassis.transform.M[14] += cabinOffset.getZ();

	Cube lapChassis(info.lapChassis_size.x, info.lapChassis_size.y, info.lapChassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lapChassis.transform);
	btVector3 lapOffset(info.lapChassis_offset.x, info.lapChassis_offset.y, info.lapChassis_offset.z);
	lapOffset = lapOffset.rotate(q.getAxis(), q.getAngle());
	lapChassis.color.Set(0., 0., 0.f, 1.f);

	lapChassis.transform.M[12] += lapOffset.getX();
	lapChassis.transform.M[13] += lapOffset.getY();
	lapChassis.transform.M[14] += lapOffset.getZ();

	Cube lapChassis2(info.lapChassis2_size.x, info.lapChassis2_size.y, info.lapChassis2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lapChassis2.transform);
	btVector3 lapOffset2(info.lapChassis2_offset.x, info.lapChassis2_offset.y, info.lapChassis2_offset.z);
	lapOffset2 = lapOffset2.rotate(q.getAxis(), q.getAngle());
	lapChassis2.color.Set(0., 0., 0.f, 1.f);

	lapChassis2.transform.M[12] += lapOffset2.getX();
	lapChassis2.transform.M[13] += lapOffset2.getY();
	lapChassis2.transform.M[14] += lapOffset2.getZ();

	Cube lapChassis3(info.lapChassis3_size.x, info.lapChassis3_size.y, info.lapChassis3_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&lapChassis3.transform);
	btVector3 lapOffset3(info.lapChassis3_offset.x, info.lapChassis3_offset.y, info.lapChassis3_offset.z);
	lapOffset3 = lapOffset3.rotate(q.getAxis(), q.getAngle());
	lapChassis3.color.Set(0., 0., 0.f, 1.f);

	lapChassis3.transform.M[12] += lapOffset3.getX();
	lapChassis3.transform.M[13] += lapOffset3.getY();
	lapChassis3.transform.M[14] += lapOffset3.getZ();

	Cube time(info.time_size.x, info.time_size.y, info.time_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&time.transform);
	btVector3 timeOffset(info.time_offset.x, info.time_offset.y, info.time_offset.z);
	timeOffset = timeOffset.rotate(q.getAxis(), q.getAngle());
	time.color.Set(1.255, 0.f, 0.f, 1.f);

	time.transform.M[12] += timeOffset.getX();
	time.transform.M[13] += timeOffset.getY();
	time.transform.M[14] += timeOffset.getZ();

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

		cabinOffset = cabinOffset.rotate(q.getAxis(), q.getAngle());
		cabinChassis.transform.M[12] += cabinOffset.getX();
		cabinChassis.transform.M[13] += cabinOffset.getY();
		cabinChassis.transform.M[14] += cabinOffset.getZ();
	}
	//Render del chassis parte por parte
	chassis.Render();
	aleronChassis.Render();
	lateralRChassis.Render();
	lateralLChassis.Render();
	lateralR1Chassis.Render();
	lateralL1Chassis.Render();
	cabinChassis.Render();
	if(firstLap)
		lapChassis.Render();
	if(secondLap)
		lapChassis2.Render();
	if(thirdLap)
		lapChassis3.Render();
	time.Render();
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