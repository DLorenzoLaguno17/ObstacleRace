#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
enum SENSOR;

enum Direction {
	VERTICAL,
	HORIZONTAL
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void CreateRail(uint number, uint space, int wallPosition, int y, int z, bool singleWall = false, Direction direction = VERTICAL);
	void CreateCylinder(float radius, float height, int x, int y, int z);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2); 
	void PutCylinderSensor(vec3 position, SENSOR sensorType, float radius, float height);

public:

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	PhysBody3D* test = nullptr;
	bool created = false;

	PhysBody3D* leftDoor = nullptr;
	PhysBody3D* rightDoor = nullptr;
	PhysBody3D* leftFrame = nullptr;
	PhysBody3D* rightFrame = nullptr; 
	PhysBody3D* block1 = nullptr;
	PhysBody3D* block2 = nullptr;
	PhysBody3D* block3 = nullptr;
	Cube* door1 = nullptr;
	Cube* door2 = nullptr;

	Cube* moving_cube1 = nullptr;
	Cube* moving_cube2 = nullptr;
	Cube* moving_cube3 = nullptr;

	vec3 pos_cube1 = { 60, 20, 115 };
	vec3 pos_cube2 = { 80, 20, 115 };
	vec3 pos_cube3 = { 100, 20, 115 };

	p2List<Cube*> cubes;
	p2List<Cylinder*>cylinders;
};
