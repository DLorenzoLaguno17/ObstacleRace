#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "PhysBody3D.h"

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
	CreateRail(11, 5, 10, 20, 0);
	CreateRail(4, 5, -25, 20, 55, true, HORIZONTAL);
	CreateRail(9, 5, -25, 20, 60, true);
	CreateRail(14, 5, -25, 20, 105, true, HORIZONTAL);
	CreateRail(3, 5, 10, 20, 55, true, HORIZONTAL);
	CreateRail(15, 5, 45, 20, 60, true);
	CreateRail(9, 5, 25, 20, 5, true);

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
	Cube* plane1 = new Cube(20, 1, 55);
	plane1->SetPos(0, 16, 27);
	plane1->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane1, MASS);
	cubes.add(plane1);

	Cube* plane2 = new Cube(65, 1, 45);
	plane2->SetPos(7, 16, 77);
	plane2->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane2, MASS);
	cubes.add(plane2);	

	Cube* plane3 = new Cube(30, 1, 55);
	plane3->SetPos(40, 16, 27);
	plane3->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane3, MASS);
	cubes.add(plane3);

	Cube* plane4 = new Cube(50, 1, 25);
	plane4->SetPos(80, 16, 12.5f);
	plane4->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane4, MASS);
	cubes.add(plane4);

	Cube* plane5 = new Cube(35, 1, 40);
	plane5->SetPos(87, 16, 45);
	plane5->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane5, MASS);
	cubes.add(plane5);
	
	Cube* plane6 = new Cube(65, 1, 65);
	plane6->SetPos(77.5f, 16, 97.5f);
	plane6->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane6, MASS);
	cubes.add(plane6);

	Cube* plane7 = new Cube(5, 1, 5);
	plane7->SetPos(117.5f, 16, 112.5f);
	plane7->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane7, MASS);
	cubes.add(plane7);

	Cube* plane8 = new Cube(5, 1, 5);
	plane8->SetPos(127.5f, 16, 112.5f);
	plane8->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane8, MASS);
	cubes.add(plane8);
	
	Cube* plane9 = new Cube(20, 1, 35);
	plane9->SetPos(145, 16, 97.5f);
	plane9->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane9, MASS);
	cubes.add(plane9);

	Cube* plane10 = new Cube(20, 1, 80);
	plane10->SetPos(125, 16, 55);
	plane10->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane10, MASS);
	cubes.add(plane10);

	Cube* plane11 = new Cube(80, 1, 20);
	plane11->SetPos(175, 16, 25);
	plane11->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane11, MASS);
	cubes.add(plane11);

	Cube* plane12 = new Cube(50, 1, 95);
	plane12->SetPos(190, 16, 82.5f);
	plane12->color.Set(White.r, White.g, White.b);
	App->physics->AddBody(*plane12, MASS);
	cubes.add(plane12);

	
	return ret;
	
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	delete test;

	/*for (p2List_item<Cube*>* cube = cubes.getFirst(); cube != nullptr; cube = cube->next)
		cubes.del(cube);*/

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (p2List_item<Cube*>* cube = cubes.getFirst(); cube != nullptr; cube = cube->next)
		cube->data->Render();

	for (p2List_item<Plane*>* plane = planes.getFirst(); plane != nullptr; plane = plane->next)
		plane->data->Render();

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
			if (!singleWall) cr->SetPos(-wallPosition, y, zpos);
			zpos += space;
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

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}