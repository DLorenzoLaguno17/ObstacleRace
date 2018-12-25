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

	// Loading sounds
	engineSound = App->audio->LoadFx("Audio/Sound Fx/engine.wav");
	drivingSound = App->audio->LoadFx("Audio/Sound Fx/car.wav");

	// Creating car
	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1.5, 5);
	car.chassis_offset.Set(0, 1.2, 0);
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

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
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
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
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
	vehicle->SetPos(0, 20, 10);
	initialCarPosition = vehicle->GetPosition();
	initialForwardVector = vehicle->GetForwardVector();

	current_time = SDL_GetTicks();
	last_time = 0;
	timer = SDL_GetTicks();

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
	current_time = SDL_GetTicks();

	// Controls of the car
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (abs(vehicle->GetKmh()) > 1 && !goingForward) {
			brake = BRAKE_POWER / 4;
			startedEngine = false;
		}
		else {
			acceleration = MAX_ACCELERATION;
			goingForward = true;

			if (!startedEngine) {
				App->audio->PlayFx(engineSound);
				startedEngine = true;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (abs(vehicle->GetKmh()) > 1 && goingForward) {
			brake = BRAKE_POWER;
			startedEngine = false;
		}
		else {
			acceleration = -MAX_ACCELERATION;
			goingForward = false;

			if (!startedEngine) {
				App->audio->PlayFx(engineSound);
				startedEngine = true;
			}
		}
	}

	// To free the camera
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		freeCamera = !freeCamera;

	// To have an aerial view
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		freeCamera = !freeCamera;
		App->camera->Position = {113, 152, 8};
		App->camera->LookAt({ 113, 0, 20 });
	}

	// The car sound is played
	if (current_time >= last_time + 2500 && abs(vehicle->GetKmh()) > 20 
		&& (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)) {
		App->audio->PlayFx(drivingSound);
		last_time = current_time;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	// To reset the level
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN || vehicle->GetPosition().y < 5)
		ResetLevel();

	vehicle->Render();

	int seconds = (int)((SDL_GetTicks() - timer) / 1000);
	int minutes = (int)(seconds / 60);

	char title[80];

	if(seconds % 60 < 10)
		sprintf_s(title, "Obstacle Race ~ Speed of the car: %.1f Km/h / Current time: 0%d:0%d", vehicle->GetKmh(), minutes, seconds % 60);
	else if(minutes < 10)
		sprintf_s(title, "Obstacle Race ~ Speed of the car: %.1f Km/h / Current time: 0%d:%d", vehicle->GetKmh(), minutes, seconds % 60);
	else
		sprintf_s(title, "Obstacle Race ~ Speed of the car: %.1f Km/h / Current time: %d:%d", vehicle->GetKmh(), minutes, seconds % 60);

	App->window->SetTitle(title);

	if (!freeCamera) {
		App->camera->LookAt(vehicle->GetPosition());
		App->camera->Position = (vehicle->GetPosition() - vehicle->GetForwardVector() * 10) + vec3(0, 4, 0);
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::ResetLevel() {
	vehicle->SetPos(initialCarPosition.x, initialCarPosition.y, initialCarPosition.z);
	vehicle->RotateBody({ 0, initialForwardVector.x, initialForwardVector.y, initialForwardVector.z });
	vehicle->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 }); 
	freeCamera = false;
	timer = SDL_GetTicks();

	App->scene_intro->block1->SetPos(App->scene_intro->pos_cube1.x, App->scene_intro->pos_cube1.y, App->scene_intro->pos_cube1.z);
	App->scene_intro->block2->SetPos(App->scene_intro->pos_cube2.x, App->scene_intro->pos_cube2.y, App->scene_intro->pos_cube2.z);
	App->scene_intro->block3->SetPos(App->scene_intro->pos_cube3.x, App->scene_intro->pos_cube3.y, App->scene_intro->pos_cube3.z);
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2) {

}