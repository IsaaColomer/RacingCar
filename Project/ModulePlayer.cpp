#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1, 0);

	car.secondChassis_size.Set(1, 1, 1);
	car.secondChassis_offset.Set(1, 1.5, 1);

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];
	
	float margin = 0.5f;

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set((half_width - 0.3f * wheel_width) + margin, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set((-half_width + 0.3f * wheel_width) - margin, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set((half_width - 0.3f * wheel_width) + margin, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set((-half_width + 0.3f * wheel_width) - margin, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 63, 10);

	vehicle->startQuat = vehicle->vehicle->getChassisWorldTransform().getRotation();
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	//Conseguir la direccion del coche para aplicar torque
	fVector = vehicle->vehicle->getForwardVector();
	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		vehicle->body->applyCentralImpulse(fVector);
		int a;
		acceleration = MAX_ACCELERATION;
		if (vehicle->GetKmh() < 70)
		{
			a = MAX_ACCELERATION + 1000;
			acceleration = a;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		vehicle->restart = true;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{/*Apliquem torque al girar, nom�s actua a l'aire es el fVector que hem trobat
		abans al principi de l'update multiplicat per la for�a que apliquem, en negatiu cap a l'esquerra*/
		vehicle->body->applyTorque(fVector * -300);
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		vehicle->body->applyTorque(fVector * 300);
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		
		int b;
		acceleration = -MAX_ACCELERATION;
		if (vehicle->GetKmh() > 10)
		{
			b = -MAX_ACCELERATION - 4000;
			acceleration = b;
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	//CAMERA MOVEMENT
	vec3 forwardVector;
	forwardVector.x = vehicle->vehicle->getForwardVector().x() + vehicle->vehicle->getChassisWorldTransform().getOrigin().x();
	forwardVector.y = vehicle->vehicle->getForwardVector().y() + vehicle->vehicle->getChassisWorldTransform().getOrigin().y();
	forwardVector.z = vehicle->vehicle->getForwardVector().z() + vehicle->vehicle->getChassisWorldTransform().getOrigin().z();

	vec3 carCamera;
	carCamera.x = vehicle->body->getCenterOfMassPosition().getX() + vehicle->vehicle->getForwardVector().x() * -10;
	carCamera.y = vehicle->body->getCenterOfMassPosition().getY() + vehicle->vehicle->getForwardVector().y() + 5;
	carCamera.z = vehicle->body->getCenterOfMassPosition().getZ() + vehicle->vehicle->getForwardVector().z() * -10;
	App->camera->Position = carCamera;

	vec3 carpos;
	carpos.x = vehicle->body->getCenterOfMassPosition().getX();
	carpos.y = vehicle->body->getCenterOfMassPosition().getY()+3;
	carpos.z = vehicle->body->getCenterOfMassPosition().getZ();

	App->camera->LookAt(carpos);

	if (vehicle->vehicle->getChassisWorldTransform().getOrigin().getY() <= 30.0f)
	{
		vehicle->SetPos(0, 63, 10);
	acceleration = 0;
	//BREAK
	for (int i = 0; i < vehicle->vehicle->getNumWheels(); ++i)
	{
		vehicle->vehicle->setBrake(500, i);
	}
		vehicle->vehicle->resetSuspension();
	if (vehicle->body->getLinearVelocity() != 0)
	{
		vehicle->body->setAngularVelocity({ 0,0,0 });
	}
	if (vehicle->GetKmh() != 0)
		vehicle->body->setLinearVelocity({ 0,0,0 });
	}

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f m/s^2 | %.1f Km/h | %.1f Y | UP AXIS: %d", acceleration, vehicle->GetKmh(), vehicle->vehicle->getChassisWorldTransform().getOrigin().getY(), vehicle->vehicle->getUpAxis());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}