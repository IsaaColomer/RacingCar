#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
public:
	bool jumpCol = false;
	bool sprintCol = false;
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	bool lap = false;
	bool checked = false;
	bool lapInv = false;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;

	PhysBody3D* cube;

	PhysBody3D* cube2;

	PhysBody3D* cube3;

	PhysBody3D* cube4;

	PhysBody3D* rampp1;

	PhysBody3D* cube6;

	PhysBody3D* cube7;

	PhysBody3D* cube8;

	PhysBody3D* cube9;

	PhysBody3D* rampp2;

	PhysBody3D* cube10;

	PhysBody3D* cube11;

	PhysBody3D* cube12;

	PhysBody3D* cube13;

	PhysBody3D* cube14;

	PhysBody3D* cube15;

	PhysBody3D* cube16;

	PhysBody3D* cube17;

	PhysBody3D* column01;
	PhysBody3D* column02;
	PhysBody3D* column03;
	PhysBody3D* column04;
	PhysBody3D* column05;
	PhysBody3D* column06;
	PhysBody3D* column07;
	PhysBody3D* column08;
	PhysBody3D* column09;
	PhysBody3D* column010;
	PhysBody3D* column011;
	PhysBody3D* cubeElev;
	PhysBody3D* arc1;
	PhysBody3D* arc2;
	PhysBody3D* arc3;

	PhysBody3D* sensor;
	PhysBody3D* sensor2;
	PhysBody3D* sensor3;
	PhysBody3D* sensorL;
	PhysBody3D* sensorI;
	PhysBody3D* checkPoint0;
	//PhysBody3D* cube1;

//	PhysBody3D* cylinder1;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;
};
