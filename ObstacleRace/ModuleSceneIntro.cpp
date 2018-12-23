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

	Plane* p = new Plane(10, 20, 10, 0);
	//App->physics->AddBody(*, MASS);
	p->color.Set(White.r, White.g, White.b);
	planes.add(p);

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

void ModuleSceneIntro::CreateRail(uint number, uint space, int position, Direction direction) {
	uint zpos = 0; 
	uint xpos = 0;

	for (int i = 0; i < number; ++i) {

		Cube* cr = new Cube(5, 8, 5);
		Cube* cl = new Cube(5, 8, 5);

		if (direction == VERTICAL) {
			zpos += space;
			cr->SetPos(-position, 20, zpos);
			cl->SetPos(position, 20, zpos);
		}
		else {
			xpos += space;
			cr->SetPos(xpos, 20, -position);
			cl->SetPos(xpos, 20, position);
		}

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