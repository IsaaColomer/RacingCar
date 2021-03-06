#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	btQuaternion quat;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	btVector3 fVector;
	btVector3 bFlipV;
	btVector3 iVector;
	bool jumped = false;
	int laps = 0;
	Timer timer;
	Timer timer2;
	float iniTime = 400;
	float totalTime = 0;

	uint winFx = 0;
	uint lostFx = 0;
	uint lapFx = 0;
};