#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 500.0f
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
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void ResetLevel();

public:

	PhysVehicle3D* vehicle;
	vec3 initialCarPosition;
	vec3 initialForwardVector;

	// Audios
	uint engineSound;
	uint drivingSound;

	// Timers
	uint last_time = 0;
	uint current_time;
	uint timer;

	float turn;
	float acceleration;
	float brake;

	bool goingForward = false;
	bool freeCamera = false;
	bool startedEngine = false;
	bool collided = false;

	bool checkpoint1_Active = false;
	bool checkpoint2_Active = false;
	bool checkpoint3_Active = false;
};