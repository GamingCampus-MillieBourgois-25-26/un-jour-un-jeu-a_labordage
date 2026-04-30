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
float prevVelocityY;
void Platformer::CollisionManagere::Update(float deltatime)
{
	if(p != nullptr)  prevVelocityY = p->velocity.y;
	player = GetOwner();

	p = player->GetComponent<Playere>();

	my_collider = GetOwner()->GetComponent<SquareCollider>();

	obj = GetOwner()->GetScene()->FindGameObject("obj");

	obj_collider = obj->GetComponent<SquareCollider>();
	p->velocity.y += gravity * deltatime;
	
	position.y += p->velocity.y * deltatime;
	position.x = p->positione.x;

	
	for (const auto& go : GetOwner()->GetScene()->GetGameObjects()) {
		if (go->GetName() == "obj") {
			sol.push_back(go.get());
		}

	}


	for (const auto& sole : sol) {
		SquareCollider* sole_collider = sole->GetComponent<SquareCollider>();
		if (SquareCollider::IsColliding(*my_collider, *sole_collider)) {
			if (GetOwner()->GetPosition().GetY() - sole_collider->GetOwner()->GetPosition().GetY() <= 0){


			if (p->velocity.y > 0) { 
				isOnGround = true;
				p->velocity.y = 0;
					 
					
				
			}
			}
		
			else if (GetOwner()->GetPosition().GetX() - sole_collider->GetOwner()->GetPosition().GetX() <= 0) {
				
					
					

					
						p->positione.x -= 1;
					


				
			}
			else if (GetOwner()->GetPosition().GetX() - sole_collider->GetOwner()->GetPosition().GetX() >= 0) {

				



				p->positione.x += 1;




			}
		}
	}
	std::cout << p->velocity.x << std::endl;
	if (prevVelocityY < 0.f && p->velocity.y >= 0.f) {
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
		p->velocity.y = 0;
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
		p->velocity.y = jumpForce;
	}
	player->SetPosition(position);
	sol.clear();
}




