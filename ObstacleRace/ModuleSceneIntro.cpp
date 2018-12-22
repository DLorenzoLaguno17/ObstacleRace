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

	// Creation of the obstacles
	Cube* test1 = new Cube(5, 10, 5);
	test1->SetPos(20, 0, 20);
	test1->color.Set(Red.r, Red.g, Red.b);
	c1 = test1;
	App->physics->AddBody(*c1, MASS);

	Cube* test2 = new Cube(5, 10, 5);
	test2->SetPos(-20, 0, 20);
	test2->color.Set(Green.r, Green.g, Green.b);
	c2 = test2;
	App->physics->AddBody(*c2, MASS);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	delete test;
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	// Rendering obstacles
	c1->Render();
	c2->Render();
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}