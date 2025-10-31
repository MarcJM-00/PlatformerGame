#pragma once

#include "Entity.h"
#include "Animation.h"
#include <box2d/box2d.h>
#include <SDL3/SDL.h>

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	// L08 TODO 6: Define OnCollision function for the player. 
	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnCollisionEnd(PhysBody* physA, PhysBody* physB);

private:

	void GodModeMove(float dt);

	void GetPhysicsValues();
	void Move();
	void Jump();
	void ApplyPhysics();
	void Draw(float dt);
	void Side();

	void Died();
	void Dash();

public:

	//Declare player parameters
	float speed = 4.0f;
	SDL_Texture* texture = NULL;

	int texW, texH;

	//Audio fx
	int pickCoinFxId;

	// L08 TODO 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;
	float jumpForce = 2.5f; // The force to apply when jumping
	bool isJumping = false; // Flag to check if the player is currently jumping
	bool isRight;
	float dashPower = 50.0f; //Fuerza del dash para impulsar al jugador
	float dashCooldownTime = 5.0f; //5 segundos de espera
	float currentCooldown = 0.0f;

	int lives = 3;
	bool isdead = false;

	bool godMode = false;

private: 
	b2Vec2 velocity;
	AnimationSet anims;

};