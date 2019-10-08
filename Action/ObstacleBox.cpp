#include "ObstacleBox.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"
#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "RotateComponent.h"
#include "Mesh.h"
#include "GameObjectManager.h"
#include <stdlib.h>
#include "SDL.h"

ObstacleBox::ObstacleBox()
	:GameObject()
	, player(nullptr)
{
	meshComp = new MeshComponent(this);
	
	srand((unsigned)(SDL_GetTicks() + rand()));
	int randNum = rand() % 3;
	Mesh* mesh = nullptr;
	switch (randNum)
	{
	case 0:
		mesh = RENDERER->GetMesh("Assets/Cube1.gpmesh");
		break;

	case 1:
		mesh = RENDERER->GetMesh("Assets/Cube2.gpmesh");
		break;

	case 2:
		mesh = RENDERER->GetMesh("Assets/Cube3.gpmesh");
		break;

	default:
		break;
	}

	meshComp->SetMesh(mesh);
	boxCollider = new BoxCollider(this, GetOnCollisionFunc());
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);
	SetScale(200.0f);
	OBSTACLE_MANAGER->AddObstacle(this);

	tag = Tag::Obstacle;

	state = Paused;
	player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);
}



ObstacleBox::~ObstacleBox()
{
	OBSTACLE_MANAGER->RemoveObstacle(this);
}

void ObstacleBox::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::Player)
	{
		//��Q���Ɠ����������̏���
		meshComp->SetVisible(false);
		ResetObstacle();
	}
}

void ObstacleBox::ResetObstacle()
{
	SetPosition(Vector3::Zero);
	state = Paused;
	boxCollider->CollisionPause();
	meshComp->SetVisible(false);
}

void ObstacleBox::UseObstacle()
{
	meshComp->SetVisible(true);
	state = Active;
	boxCollider->CollisionActive();
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

void ObstacleBox::UpdateGameObject(float _deltaTime)
{
	if (player->GetPosition().x - 500.0f > position.x)
	{
		ResetObstacle();
	}
}
