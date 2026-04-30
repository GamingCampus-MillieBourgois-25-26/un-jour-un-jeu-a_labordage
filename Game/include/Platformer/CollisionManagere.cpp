#include "pch.h"
#include "Platformer/CollisionManagere.h"

// Tous les includes lourds ici, pas dans le .h
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "Platformer/Playere.h"
#include <iostream>

void Platformer::CollisionManagere::Start()
{

}

void Platformer::CollisionManagere::Update(float deltatime)
{
	float prevVelocityY = velocity.y;
	player = GetOwner();

	p = player->GetComponent<Playere>();

	my_collider = GetOwner()->GetComponent<SquareCollider>();

	obj = GetOwner()->GetScene()->FindGameObject("obj");

	obj_collider = obj->GetComponent<SquareCollider>();
	velocity.y += gravity * deltatime;
	position.y += velocity.y * deltatime;
	position.x = p->positione.x;

	
	for (const auto& go : GetOwner()->GetScene()->GetGameObjects()) {
		if (go->GetName() == "obj") {
			sol.push_back(go.get());
		}

	}


	for (const auto& sole : sol) {
		SquareCollider* sole_collider = sole->GetComponent<SquareCollider>();
		if (SquareCollider::IsColliding(*my_collider, *sole_collider)) {
			if (velocity.y > 0) { 
				isOnGround = true;
				position.y = sole->GetPosition().y - ((sole_collider->GetHeight()/2) + (my_collider->GetHeight()/3.f));
					 
					
				
			}
			
		}
	}

	if (prevVelocityY < 0.f && velocity.y >= 0.f) {
		isBackflipping = true;
	}

	if (isBackflipping) {
		if (p->right) {
			if (currentRotation <= 360)
				currentRotation += backflipSpeed * deltatime;
		}
	
	if (p->left) {
		if (currentRotation >= -360)
			currentRotation -= backflipSpeed * deltatime;
	}

		
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

	

	else {
		isOnGround = false;
	}
	if (p->isJump) {
		velocity.y = jumpForce;
	}
	player->SetPosition(position);
	sol.clear();
}




