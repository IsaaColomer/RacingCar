#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	Cube c1(20,2,100);
	Cube c2(10,2,100);
	Cube c3(10,2,100);
	Cube c4(100,2,10);
	Cube ramp1(10, 10, 20);
	Cube c6(10, 2, 10);
	Cube c7(10, 2, 10);
	Cube c8(17, 2, 17);
	Cube c9(50, 2, 20);
	Cube ramp2(20, 2, 20);
	Cube c10(200, 2, 20);
	Cube c11(200, 2, 20);
	Cube c12(170, 60, 2);
	Cube c13(130, 2, 20);
	Cube c14(240, 2, 20);
	Cube c15(200, 2, 20);
	Cube c16(10, 2, 200);
	Cube c17(100, 2, 50);
	Cube column1(2, 8, 2);
	Cube column2(2, 8, 2);
	Cube column3(2, 8, 2);
	Cube column4(2, 8, 2);
	Cube column5(2, 8, 2);
	Cube column6(2, 8, 2);
	Cube column7(2, 8, 2);
	Cube column8(2, 8, 2);
	Cube column9(2, 8, 2);
	Cube column10(2, 8, 2);
	Cube column11(2, 8, 2);
	//Cylinder cyl1(20, 20);

	ramp1.SetRotation(-20, { 1,0,0 });
	ramp2.SetRotation(-20, { 0,0,1 });
	c13.SetRotation(20, { 0,0,1 });
	c15.SetRotation(5, { 0,0,1 });
	c16.SetRotation(10, { 1,0,0 });
	c17.SetRotation(30, { 1,0,0 });
	column1.SetRotation(10, {0,1,0});
	column2.SetRotation(10, {0,1,0});
	column4.SetRotation(10, {0,1,0});
	column5.SetRotation(-10, {1,0,0});
	column6.SetRotation(-10, {1,0,0});
	column7.SetRotation(-10, {1,0,0});
	column8.SetRotation(10, {1,0,0});
	column9.SetRotation(10, {1,0,0});
	column10.SetRotation(10, {1,0,0});
	column11.SetRotation(5, {1,0,0});
	//cyl1.SetRotation(-90,{0, 1, 0});
	
	cube = App->physics->AddBody(c1,0);
	cube2 = App->physics->AddBody(c2,0);
	cube3 = App->physics->AddBody(c3,0);
	cube4 = App->physics->AddBody(c4,0);
	rampp1 = App->physics->AddBody(ramp1,0);
	cube6 = App->physics->AddBody(c6,0);
	cube7 = App->physics->AddBody(c7,0);
	cube8 = App->physics->AddBody(c8,0);
	rampp2 = App->physics->AddBody(ramp2,0);
	cube9 = App->physics->AddBody(c9, 0);
	cube10 = App->physics->AddBody(c10, 0);
	cube11 = App->physics->AddBody(c11, 0);
	cube12 = App->physics->AddBody(c12, 0);
	cube13 = App->physics->AddBody(c13, 0);
	cube14 = App->physics->AddBody(c14, 0);
	cube15 = App->physics->AddBody(c15, 0);
	cube16 = App->physics->AddBody(c16, 0);
	cube17 = App->physics->AddBody(c17, 0);
	column01 = App->physics->AddBody(column1, 0);
	column02 = App->physics->AddBody(column2, 0);
	column03 = App->physics->AddBody(column3, 0);
	column04 = App->physics->AddBody(column4, 0);
	column05 = App->physics->AddBody(column5, 0);
	column06 = App->physics->AddBody(column6, 0);
	column07 = App->physics->AddBody(column7, 0);
	column08 = App->physics->AddBody(column8, 0);
	column09 = App->physics->AddBody(column9, 0);
	column010 = App->physics->AddBody(column10, 0);
	column011 = App->physics->AddBody(column11, 0);
	//cylinder1 = App->physics->AddBody(cyl1, 0);
	

	cube->SetPos(0, 60, 0);
	cube2->SetPos(0, 60, 100);
	cube3->SetPos(0, 60, 200);
	cube4->SetPos(-50, 60, 200);
	rampp1->SetPos(0, 60, 100);
	cube6->SetPos(-100, 60, 190);
	cube7->SetPos(-120, 60, 180);
	cube8->SetPos(-140, 60, 160);
	cube9->SetPos(-175, 60, 160);
	rampp2->SetPos(-210, 63, 160);
	cube10->SetPos(-350, 40, 160);
	cube11->SetPos(-350, 40, 140);
	cube12->SetPos(-330, 50, 150);
	cube13->SetPos(-250, 40, 140);
	cube14->SetPos(-100, 40, 140);
	cube15->SetPos(-40, 42, 140);
	cube16->SetPos(52, 56, 92);
	cube17->SetPos(0, 70, -30);
	column01->SetPos(-76, 42, 140);
	column02->SetPos(0, 50, 135);
	column03->SetPos(0, 50, 147);
	column04->SetPos(-60, 44, 133);
	column05->SetPos(-60, 44, 143);
	column06->SetPos(-50, 46, 138);
	column07->SetPos(-40, 46, 144);
	column08->SetPos(-40, 46, 134);
	column09->SetPos(-25, 46, 140);
	column010->SetPos(-13, 48, 140);
	column011->SetPos(20, 50, 140);
	//cube16->SetPos(-40, 42, 140);
	//cylinder1->SetPos(0, 60, 100);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	Cube cube_road(20,2,100);
	Cube cube_road2(10,2,100);
	Cube cube_road3(10,2,100);
	Cube cube_road4(100, 2, 10);
	Cube ramp1(10, 5, 20);
	Cube cube_road6(10, 2, 10);
	Cube cube_road7(10, 2, 10);
	Cube cube_road8(17, 2, 17);
	Cube cube_road9(50, 2, 20);
	Cube ramp2(20, 2, 20);
	Cube cube_road10(200, 2, 20);
	Cube cube_road11(200, 2, 20);
	Cube cube_road12(170, 60, 2);
	Cube cube_road13(130, 2, 20);
	Cube cube_road14(110, 2, 20);
	Cube cube_road15(200, 2, 20);
	Cube cube_road16(10, 2, 200);
	Cube cube_road17(100, 2, 50);
	Cube column1(2, 8, 2);
	Cube column2(2, 8, 2);
	Cube column3(2, 8, 2);
	Cube column4(2, 8, 2);
	Cube column5(2, 8, 2);
	Cube column6(2, 8, 2);
	Cube column7(2, 8, 2);
	Cube column8(2, 8, 2);
	Cube column9(2, 8, 2);
	Cube column10(2, 8, 2);
	Cube column11(2, 8, 2);
	//Cylinder cylinder_jump(20,20);

	p.axis = true;
	p.Render();
	
	cube_road.wire = false;
	cube_road.SetPos(0, 60, 0);
	cube_road.color = Blue;
	cube_road.Render();

	cube_road2.wire = false;
	cube_road2.SetPos(0, 60,100);
	cube_road2.color = Red;
	cube_road2.Render();

	cube_road3.wire = false;
	cube_road3.SetPos(0, 60, 200);
	cube_road3.color = Green;
	cube_road3.Render();

	cube_road4.wire = false;
	cube_road4.SetPos(-50, 60, 200);
	cube_road4.color = Green;
	cube_road4.Render();

	ramp1.wire = false;
	ramp1.SetPos(0, 62, 100);
	ramp1.SetRotation(-20, { 1,0,0 });
	ramp1.color = Blue;
	ramp1.Render();

	cube_road6.wire = false;
	cube_road6.SetPos(-100, 60, 190);
	cube_road6.color = Blue;
	cube_road6.Render();

	cube_road7.wire = false;
	cube_road7.SetPos(-120, 60, 180);
	cube_road7.color = Blue;
	cube_road7.Render();

	cube_road8.wire = false;
	cube_road8.SetPos(-140, 60, 160);
	cube_road8.color = Blue;
	cube_road8.Render();

	cube_road9.wire = false;
	cube_road9.SetPos(-175, 60, 160);
	cube_road9.color = Blue;
	cube_road9.Render();

	ramp2.wire = false;
	ramp2.SetPos(-210, 63, 160);
	ramp2.SetRotation(-20, { 0,0,1 });
	ramp2.color = Blue;
	ramp2.Render();

	cube_road10.wire = false;
	cube_road10.SetPos(-350, 40, 160);
	cube_road10.color = Blue;
	cube_road10.Render();

	cube_road11.wire = false;
	cube_road11.SetPos(-350, 40, 140);
	cube_road11.color = Red;
	cube_road11.Render();

	cube_road12.wire = false;
	cube_road12.SetPos(-330, 50, 150);
	cube_road12.color = Red;
	cube_road12.Render();

	cube_road13.SetRotation(20, { 0,0,1 });
	cube_road13.wire = false;
	cube_road13.SetPos(-250, 40, 140);
	cube_road13.color = White;
	cube_road13.Render();

	cube_road14.wire = false;
	cube_road14.SetPos(-100, 40, 140);
	cube_road14.color = White;
	cube_road14.Render();

	cube_road15.SetRotation(5, { 0,0,1 });
	cube_road15.wire = false;
	cube_road15.SetPos(-40, 42, 140);
	cube_road15.color = White;
	cube_road15.Render();

	cube_road16.SetRotation(10, { 1,0,0 });
	cube_road16.wire = false;
	cube_road16.SetPos(52, 56, 92);
	cube_road16.color = White;
	cube_road16.Render();

	cube_road17.SetRotation(30, { 1,0,0 });
	cube_road17.wire = false;
	cube_road17.SetPos(0, 70, -30);
	cube_road17.color = Red;
	cube_road17.Render();

	column1.SetRotation(10, { 1,0,0 });
	column1.wire = false;
	column1.SetPos(-76, 42, 140);
	column1.color = Red;
	column1.Render();

	column2.SetRotation(10, { 0,1,0 });
	column2.wire = false;
	column2.SetPos(0, 50, 135);
	column2.color = Red;
	column2.Render();

	column3.SetRotation(10, { 0,1,0 });
	column3.wire = false;
	column3.SetPos(0, 50, 147);
	column3.color = Red;
	column3.Render();

	column4.SetRotation(10, { 1,0,0 });
	column4.wire = false;
	column4.SetPos(-60, 44, 133);
	column4.color = Red;
	column4.Render();

	column5.SetRotation(-10, { 1,0,0 });
	column5.wire = false;
	column5.SetPos(-60, 44, 143);
	column5.color = Red;
	column5.Render();

	column6.SetRotation(-10, { 1,0,0 });
	column6.wire = false;
	column6.SetPos(-50, 46, 138);
	column6.color = Red;
	column6.Render();

	column7.SetRotation(-10, { 1,0,0 });
	column7.wire = false;
	column7.SetPos(-40, 46, 144);
	column7.color = Red;
	column7.Render();

	column8.SetRotation(10, { 1,0,0 });
	column8.wire = false;
	column8.SetPos(-40, 46, 134);
	column8.color = Red;
	column8.Render();

	column9.SetRotation(10, { 1,0,0 });
	column9.wire = false;
	column9.SetPos(-25, 46, 140);
	column9.color = Red;
	column9.Render();

	column10.SetRotation(10, { 1,0,0 });
	column10.wire = false;
	column10.SetPos(-13, 48, 140);
	column10.color = Red;
	column10.Render();

	column11.SetRotation(5, { 1,0,0 });
	column11.wire = false;
	column11.SetPos(20, 50, 140);
	column11.color = Red;
	column11.Render();

	//cylinder_jump.wire = false;
	//cylinder_jump.SetPos(0, 60, 100);
	//cylinder_jump.SetRotation(-90, { 0,1,0 });
	//cylinder_jump.color = Red;
	//cylinder_jump.Render();

	myCurva pa(0, 0, 0, 10, 5, 180);
	pa.wire = false;
	pa.color = Green;
	pa.SetPos(20, 0, 40);
	pa.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

