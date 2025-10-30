#include "Engine.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Log.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"
#include "Map.h"
#include "Item.h"

Scene::Scene() : Module()
{
	name = "scene";
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	//Con esto iniciamos al jugador
	player = std::dynamic_pointer_cast<Player>(Engine::GetInstance().entityManager->CreateEntity(EntityType::PLAYER));
	
	//Con esto creamos los objetos que se pueden coger
	std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(Engine::GetInstance().entityManager->CreateEntity(EntityType::ITEM));
	std::shared_ptr<Item> item2 = std::dynamic_pointer_cast<Item>(Engine::GetInstance().entityManager->CreateEntity(EntityType::ITEM));
	item->position = Vector2D(200, 200);
	item2->position = Vector2D(300, 200);

	return ret;
}

// Called before the first frame
bool Scene::Start()
{

	//Engine::GetInstance().audio->PlayMusic("Assets/Audio/Music/level-iv-339695.wav");

	//L06 TODO 3: Call the function to load the map. 
	Engine::GetInstance().map->Load("Assets/Maps/", "Nivel.tmx");
	
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (player != nullptr) // Asegúrate de que el protagonista exista
	{
		// Con esto hacemos que la camara siga al jugador
		Engine::GetInstance().render->camera.x = -(int)player->position.getX() + (Engine::GetInstance().window->window_width/2);
		Engine::GetInstance().render->camera.y = -(int)player->position.getY() + (Engine::GetInstance().window->window_height/2);

		// Con esto podemos definir los limites de altura y lados de la camara
		if (Engine::GetInstance().render->camera.x > 0) Engine::GetInstance().render->camera.x = 0;
		if (Engine::GetInstance().render->camera.y < 0 || Engine::GetInstance().render->camera.y < Engine::GetInstance().window->window_height/2) Engine::GetInstance().render->camera.y = 0;

	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(Engine::GetInstance().input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
