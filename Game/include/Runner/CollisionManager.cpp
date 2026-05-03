#include "pch.h"
#include "CollisionManager.h"

// Tous les includes lourds ici, pas dans le .h
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "Runner/Player.h"
#include <iostream>

void Runner::CollisionManager::Start()
{
   
}

void Runner::CollisionManager::Update(float deltatime)
{
	float prevVelocityY = velocity.y;
	player = GetOwner();

	p = player->GetComponent<Player>();

	my_collider = GetOwner()->GetComponent<SquareCollider>();

	obj = GetOwner()->GetScene()->FindGameObject("obj");

	obj_collider = obj->GetComponent<SquareCollider>();
	velocity.y += gravity * deltatime;
	position.y += velocity.y * deltatime;
	position.x = 200;

	/*	player->SetPosition(position);*/

	if (prevVelocityY < 0.f && velocity.y >= 0.f) {
		isBackflipping = true;
	}

	if (isBackflipping) {
		if(currentRotation <=360)
		currentRotation += backflipSpeed * deltatime;
		player->SetRotation(sf::degrees(currentRotation));
	}

	if (isOnGround) {
		velocity.y = 0;
		isBackflipping = false;
		currentRotation = 0.f;
		player->SetRotation(sf::degrees(0.f));
	}
	if (!isOnGround) {
		p->isJump = false;
	}

	if (SquareCollider::IsColliding(*my_collider, *obj_collider)) {
		
		isOnGround = true;

	}
	
	else {
		isOnGround = false;
	}
	if (p->isJump) {
		velocity.y = jumpForce;
	}
	player->SetPosition(position);
}

    
