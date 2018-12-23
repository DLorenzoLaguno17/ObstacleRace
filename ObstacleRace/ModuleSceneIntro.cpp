#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "PhysBody3D.h"

#define MASS 50000

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
	CreateRail(10, 7, 10);

	int xpos = -17;

	for (int i = 0; i < 4; ++i) {
		xpos += 7;
		Cube* c = new Cube(5, 8, 5);
		c->SetPos(xpos, 0, 0);

		if (i % 2 == 0)
			c->color.Set(Red.r, Red.g, Red.b);
		else 
			c->color.Set(White.r, White.g, White.b);

		App->physics->AddBody(*c, MASS);
		cubes.add(c);
	}

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

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::CreateRail(uint number, uint space, int x) {
	uint zpos = 0;

	for (int i = 0; i < number; ++i) {
		zpos += space;
		Cube* cr = new Cube(5, 8, 5);
		cr->SetPos(-x, 0, zpos);
		Cube* cl = new Cube(5, 8, 5);
		cl->SetPos(x, 0, zpos);

		if (i % 2 == 0) {
			cr->color.Set(Red.r, Red.g, Red.b);
			cl->color.Set(Red.r, Red.g, Red.b);
		}
		else {
			cr->color.Set(White.r, White.g, White.b);
			cl->color.Set(White.r, White.g, White.b);
		}

		App->physics->AddBody(*cr, MASS);
		cubes.add(cr);
		App->physics->AddBody(*cl, MASS);
		cubes.add(cl);
	}
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}