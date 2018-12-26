#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModuleAudio.h"

#define MASS 0

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

	App->camera->Move(vec3(0.0f, 0.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Playing the music
	App->audio->PlayMusic("Audio/Music/music.ogg");

	// Creation of the level

	// Outer walls
	CreateRail(11, 5, 10, 20, 0);
	CreateRail(4, 5, -25, 20, 55, true, HORIZONTAL);
	CreateRail(9, 5, -25, 20, 60, true);
	CreateRail(14, 5, -25, 20, 100, true, HORIZONTAL);
	CreateRail(3, 5, 10, 20, 55, true, HORIZONTAL);
	CreateRail(13, 5, 45, 20, 65, true);
	CreateRail(9, 5, 40, 20, 55, true);
	CreateRail(11, 5, 25, 20, 5, true);
	CreateRail(17, 5, 25, 20, 0, true, HORIZONTAL);
	CreateRail(3, 5, 40, 20, 55, true, HORIZONTAL);
	CreateRail(5, 5, 55, 20, 30, true);
	CreateRail(4, 5, 55, 20, 25, true, HORIZONTAL);
	CreateRail(7, 5, 70, 20, 30, true);
	CreateRail(7, 5, 50, 20, 65, true, HORIZONTAL);
	CreateRail(21, 5, 110, 20, 5, true);
	CreateRail(2, 5, 110, 20, 125, true);
	CreateRail(12, 5, 50, 20, 130, true, HORIZONTAL);
	CreateRail(5, 5, 115, 20, 95, true, HORIZONTAL);
	CreateRail(5, 5, 115, 20, 110, true, HORIZONTAL);
	CreateRail(8, 5, 115, 20, 120, true, HORIZONTAL);
	CreateRail(6, 5, 107.5f, 12, 110, true, HORIZONTAL);
	CreateRail(6, 5, 107.5f, 12, 120, true, HORIZONTAL);
	CreateRail(17, 5, 115, 20, 15, true);
	CreateRail(2, 5, 135, 20, 100, true);
	CreateRail(8, 5, 155, 20, 80, true);
	CreateRail(9, 5, 135, 20, 35, true);
	CreateRail(3, 5, 140, 20, 75, true, HORIZONTAL);
	CreateRail(20, 5, 120, 20, 15, true, HORIZONTAL);
	CreateRail(9, 5, 140, 20, 35, true, HORIZONTAL);
	CreateRail(22, 5, 215, 20, 20, true);
	CreateRail(9, 5, 170, 20, 130, true, HORIZONTAL);
	CreateRail(18, 5, 165, 20, 40, true);

	// ------------------------------------------------------
	// OBSTACLES
	// ------------------------------------------------------
	
	// First room
	CreateRail(3, 15, -10, 20, 65, true);
	CreateRail(2, 15, 5, 20, 72.5f, true);
	CreateRail(3, 15, 20, 20, 65, true);

	//Cylinder
	PutCylinderSensor({ 40, 20, 35 }, DEATH, 5, 8);

	// Mid labirynth
	CreateRail(2, 5, 60, 20, 15, true);
	CreateRail(2, 5, 90, 20, 5, true);
	CreateRail(3, 5, 75, 20, 5, true);
	CreateRail(5, 5, 85, 20, 20, true, HORIZONTAL);
	CreateRail(2, 5, 100, 20, 35, true, HORIZONTAL);
	CreateRail(4, 5, 75, 20, 35, true, HORIZONTAL);
	CreateRail(3, 5, 85, 20, 50, true, HORIZONTAL);
	CreateRail(8, 5, 95, 20, 50, true);
	CreateRail(5, 5, 85, 20, 90, true, HORIZONTAL);

	//three moving cubes
	moving_cube1 = new Cube(4, 4, 4);
	moving_cube1->SetPos(60, 20, 115);
	moving_cube1->color.Set(Blue.r, Blue.g, Blue.b);
	block1 = App->physics->AddBody(*moving_cube1, 30);
	cubes.add(moving_cube1);

	moving_cube2 = new Cube(4, 4, 4);
	moving_cube2->SetPos(80, 20, 115);
	moving_cube2->color.Set(Blue.r, Blue.g, Blue.b);
	block2 =App->physics->AddBody(*moving_cube2, 30);
	cubes.add(moving_cube2);

	moving_cube3 = new Cube(4, 4, 4);
	moving_cube3->SetPos(100, 20, 115);
	moving_cube3->color.Set(Blue.r, Blue.g, Blue.b);
	block3 = App->physics->AddBody(*moving_cube3, 30);
	cubes.add(moving_cube3);

	// After jump horizontals
	CreateRail(2, 5, 120, 20, 35, true, HORIZONTAL);
	CreateRail(1, 5, 120, 20, 60, true, HORIZONTAL);
	CreateRail(1, 5, 130, 20, 50, true, HORIZONTAL);
	CreateRail(2, 5, 125, 20, 75, true, HORIZONTAL);

	// Cylindric obstacles	
	PutCylinderSensor({ 125, 20, 23 }, DEATH, 3, 8);
	PutCylinderSensor({ 140, 20, 20 }, DEATH, 1, 8);
	PutCylinderSensor({ 150, 20, 32 }, DEATH, 7, 8);
	PutCylinderSensor({ 166, 20, 18 }, DEATH, 5, 8);
	PutCylinderSensor({ 185, 20, 35 }, DEATH, 9, 8);

	// Labirynth

	CreateRail(5, 5, 180, 20, 50, true, HORIZONTAL);
	CreateRail(7, 5, 190, 20, 55, true);
	CreateRail(2, 5, 175, 20, 70, true, HORIZONTAL);
	CreateRail(2, 5, 170, 20, 75, true, HORIZONTAL);
	CreateRail(4, 5, 175, 20, 90, true, HORIZONTAL);
	CreateRail(2, 5, 205, 20, 100, true, HORIZONTAL);
	CreateRail(2, 5, 195, 20, 95, true, HORIZONTAL);
	CreateRail(2, 5, 195, 20, 115, true, HORIZONTAL);
	CreateRail(5, 5, 170, 20, 110, true, HORIZONTAL);
	CreateRail(3, 5, 200, 20, 75, true, HORIZONTAL);




	// Creating the doors
	Cube* cr = new Cube(5, 8, 5);
	Cube* cl = new Cube(5, 8, 5);
	cl->SetPos(10, 20, 55);
	cr->SetPos(-10, 20, 55);
	cr->color.Set(Green.r, Green.g, Green.b);
	cl->color.Set(Green.r, Green.g, Green.b);
	leftFrame = App->physics->AddBody(*cl, MASS);
	cubes.add(cl);
	rightFrame = App->physics->AddBody(*cr, MASS);
	cubes.add(cr);

	door1 = new Cube(6.5, 8, 1);
	door1->SetPos(3, 20, 55);
	door1->color.Set(Blue.r, Blue.g, Blue.b);
	door2 = new Cube(6.5, 8, 1);
	door2->SetPos(-3, 20, 55);
	door2->color.Set(Blue.r, Blue.g, Blue.b);
	leftDoor = App->physics->AddBody(*door1, 1);
	cubes.add(door1);
	rightDoor = App->physics->AddBody(*door2, 1);
	cubes.add(door2);

	App->physics->AddConstraintP2P(*rightDoor, *rightFrame, { -4, 2, 0 }, { 3.5, 2, 0 });
	App->physics->AddConstraintP2P(*rightDoor, *rightFrame, { -4, -2, 0 }, { 2.5, -2, 0 });
	App->physics->AddConstraintP2P(*leftDoor, *leftFrame, { 4, 2, 0 }, { -3.5, 2, 0 });
	App->physics->AddConstraintP2P(*leftDoor, *leftFrame, { 4, -2, 0 }, { -2.5, -2, 0 });

	int xpos = -15;

	for (int i = 0; i < 4; ++i) {
		xpos += 5;
		Cube* c = new Cube(5, 8, 5);
		c->SetPos(xpos, 20, 0);

		if (i % 2 == 0)
			c->color.Set(Green.r, Green.g, Green.b);
		else
			c->color.Set(White.r, White.g, White.b);

		App->physics->AddBody(*c, MASS);
		cubes.add(c);
	}

	// Creating the floor

	CreateCube(20, 1, 55, 0, 16, 27);
	CreateCube(65,1,45,7,16,77);
	CreateCube(30, 1, 55, 40, 16, 27);
	CreateCube(55,1,25,82.5,16,12.5);
	CreateCube(40, 1, 40, 90, 16, 45);
	CreateCube(65, 1, 65, 75.5, 16, 97.5f);
	CreateCube(5, 1, 5, 117.5, 16, 115);
	CreateCube(5, 1, 5, 127.5, 16, 115);
	CreateCube(7.07, 8, 1, 110.5, 20, 109.5,true, -45, { 0,1,0 });
	CreateCube(7.07, 8, 1, 110.5, 20, 120.5,true, 45, { 0,1,0 });
	CreateCube(7.07, 8, 1, 105.5, 20, 94.5, true, -45, { 0,1,0 });
	CreateCube(7.07, 8, 1, 105.5, 20, 125.5, true, 45, { 0,1,0 });
	CreateCube(5,1,5, 112.5, 12, 115);
	CreateCube(5, 1, 5, 112.5, 12, 115);
	CreateCube(5,1,5, 132.5, 12, 115);
	CreateCube(20,  1, 40, 145, 16, 97.5);
	CreateCube(20, 1, 80, 125, 16, 55);
	CreateCube(80, 1, 20, 175, 16, 25);
	CreateCube(50, 1, 75, 190, 16, 72.5);
	CreateCube(20, 1, 20, 205, 16, 120);
	CreateCube(20, 1, 20, 186.67, 11, 120,true, 30, { 0, 0, 1 });
	CreateCube(20, 1, 20, 168.34, 6, 120);
	CreateCube(5, 1, 30, 168.34, 6, 95);
	CreateCube(4, 1, 20, 168.34, 6, 70);
	CreateCube(20, 1, 20, 160, 6, 50);
	CreateCube(10, 1, 5, 145, 6, 37.5);
	CreateCube(10, 1, 5, 135, 6, 32.5);
	CreateCube(10, 1, 5, 125, 6, 27.5);
	CreateCube(10, 1, 5, 115, 6, 22.5);
	CreateCube(10, 1, 5, 105, 6, 22.5);
	CreateCube(10, 1, 5, 95, 6, 27.5);
	CreateCube(10, 1, 5, 85, 6, 32.5);
	CreateCube(10, 1, 5, 75, 6, 37.5);
	CreateCube(10, 1, 40, 75, 6, 60);
	CreateCube(10, 1, 5, 75, 6, 85.5);
	CreateCube(10, 1, 5, 75, 6, 92.5);
	CreateCube(10, 1, 5, 75, 6, 100.5);
	CreateCube(10, 1, 20, 75, 6, 113);

	CreateCube(20, 1, 20, 75, 6, 133);

	PutCylinderSensor({ 75, 10, 133 }, WIN, 3, 8);

	PutCylinderSensor({ 87.5, 17, 65 }, CHECKPOINT1, 5, 1);
	PutCylinderSensor({ 125, 17, 42.5 }, CHECKPOINT2, 5, 1);
	PutCylinderSensor({ 208, 17, 113 }, CHECKPOINT3, 5, 1);

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
	p.axis = true;
	p.Render();

	leftDoor->GetTransform(&door1->transform);
	rightDoor->GetTransform(&door2->transform);
	block1->GetTransform(&moving_cube1->transform);
	block2->GetTransform(&moving_cube2->transform);
	block3->GetTransform(&moving_cube3->transform);

	for (p2List_item<Cube*>* cube = cubes.getFirst(); cube != nullptr; cube = cube->next)
		cube->data->Render();

	for (p2List_item<Cylinder*>* cylinder = cylinders.getFirst(); cylinder != nullptr; cylinder = cylinder->next)
		cylinder->data->Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::CreateRail(uint number, uint space, int wallPosition, int y, int z, bool singleWall, Direction direction) {
	int zpos = z; 
	int xpos = wallPosition;

	for (int i = 0; i < number; ++i) {

		Cube* cr = new Cube(5, 8, 5);
		Cube* cl = new Cube(5, 8, 5);

		if (direction == VERTICAL) {
			cl->SetPos(wallPosition, y, zpos);
			zpos += space;
			if (!singleWall) cr->SetPos(-wallPosition, y, zpos);
		}
		else {
			cl->SetPos(xpos, y, z);
			xpos += space;
			if (!singleWall) cr->SetPos(xpos, y, -wallPosition);
		}

		if (i % 2 == 0) {
			if (!singleWall) cr->color.Set(Green.r, Green.g, Green.b);
			cl->color.Set(Green.r, Green.g, Green.b);
		}
		else {
			if (!singleWall) cr->color.Set(White.r, White.g, White.b);
			cl->color.Set(White.r, White.g, White.b);
		}

		App->physics->AddBody(*cl, MASS);
		cubes.add(cl);
		if (!singleWall) {
			App->physics->AddBody(*cr, MASS);
			cubes.add(cr);
		}

		if (singleWall) delete cr;
	}
}

void ModuleSceneIntro::CreateCube(float xcube, float height, float ycube, float x, float y, float z, bool rotated, float angle, vec3 u) {
	Cube* plane1 = new Cube(xcube, height, ycube);
	plane1->SetPos(x, y, z);
	if (rotated)plane1->SetRotation(angle, u);
	plane1->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane1, MASS);
	cubes.add(plane1);
}

void ModuleSceneIntro::PutCylinderSensor(vec3 position, SENSOR sensorType, float radius, float height) {

	Cylinder* cylinder = new Cylinder(radius, height);
	cylinder->SetRotation(90, { 0,0,1 });
	cylinder->SetPos(position.x, position.y, position.z);

	if(sensorType == DEATH)
		cylinder->color.Set(Red.r, Red.g, Red.b);
	else if (sensorType == WIN)
		cylinder->color.Set(Blue.r, Blue.g, Blue.b);
	else
		cylinder->color.Set(Yellow.r, Yellow.g, Yellow.b);

	PhysBody3D* sensor = App->physics->AddBody(*cylinder, MASS, sensorType);
	cylinders.add(cylinder);

	sensor->body->setCollisionFlags(sensor->body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	sensor->collision_listeners.add(this);
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->sensorType == DEATH)
		App->player->collided = true;
	else if (body1->sensorType == CHECKPOINT1)
		App->player->checkpoint1_Active = true;
	else if (body1->sensorType == CHECKPOINT2)
		App->player->checkpoint2_Active = true;
	else if (body1->sensorType == CHECKPOINT3)
		App->player->checkpoint3_Active = true;
	else if (body1->sensorType == WIN) {}

}