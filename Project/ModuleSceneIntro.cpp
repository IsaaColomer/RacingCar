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
	Cube c6(20, 2, 20);
	Cube c7(20, 2, 20);
	Cube c8(20, 2, 20);
	Cube c9(50, 2, 20);
	Cube ramp2(20, 10, 20);


	ramp1.SetRotation(-20, { 1,0,0 });
	ramp2.SetRotation(-20, { 0,0,1 });
	
	cube = App->physics->AddBody(c1,0);
	cube2 = App->physics->AddBody(c2,0);
	cube3 = App->physics->AddBody(c3,0);
	cube4 = App->physics->AddBody(c4,0);
	rampp1 = App->physics->AddBody(ramp1,0);
	cube6 = App->physics->AddBody(c6,0);
	cube7 = App->physics->AddBody(c7,0);
	cube8 = App->physics->AddBody(c8,0);
	cube9 = App->physics->AddBody(c9,0);
	rampp2 = App->physics->AddBody(ramp2,0);

	cube->SetPos(0, 20, 0);
	cube2->SetPos(0, 20, 100);
	cube3->SetPos(0, 20, 200);
	cube4->SetPos(-50, 20, 200);
	rampp1->SetPos(0, 20, 100);
	cube6->SetPos(-100, 20, 190);
	cube7->SetPos(-120, 20, 180);
	cube8->SetPos(-140, 20, 160);
	cube9->SetPos(-175, 20, 160);
	rampp2->SetPos(-210, 19, 160);

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
	Cube cube_road6(20, 2, 20);
	Cube cube_road7(20, 2, 20);
	Cube cube_road8(20, 2, 20);
	Cube cube_road9(50, 2, 20);
	Cube ramp2(20, 10, 20);

	p.axis = true;
	p.Render();
	
	cube_road.wire = false;
	cube_road.SetPos(0, 20, 0);
	cube_road.color = Blue;
	cube_road.Render();

	cube_road2.wire = false;
	cube_road2.SetPos(0,20,100);
	cube_road2.color = Red;
	cube_road2.Render();

	cube_road3.wire = false;
	cube_road3.SetPos(0, 20, 200);
	cube_road3.color = Green;
	cube_road3.Render();

	cube_road4.wire = false;
	cube_road4.SetPos(-50, 20, 200);
	cube_road4.color = Green;
	cube_road4.Render();

	ramp1.wire = false;
	ramp1.SetPos(0, 22, 100);
	ramp1.SetRotation(-20, { 1,0,0 });
	ramp1.color = Blue;
	ramp1.Render();

	cube_road6.wire = false;
	cube_road6.SetPos(-100, 20, 190);
	cube_road6.color = Blue;
	cube_road6.Render();

	cube_road7.wire = false;
	cube_road7.SetPos(-120, 20, 180);
	cube_road7.color = Blue;
	cube_road7.Render();

	cube_road8.wire = false;
	cube_road8.SetPos(-140, 20, 160);
	cube_road8.color = Blue;
	cube_road8.Render();

	cube_road9.wire = false;
	cube_road9.SetPos(-175, 20, 160);
	cube_road9.color = Blue;
	cube_road9.Render();

	ramp2.wire = false;
	ramp2.SetPos(-210, 19, 160);
	ramp2.SetRotation(-20, { 0,0,1 });
	ramp2.color = Blue;
	ramp2.Render();


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

