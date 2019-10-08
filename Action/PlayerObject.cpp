#include "PlayerObject.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "SphereCollider.h"
#include "MainCamera.h"
#include "AutoRunComponent.h"
#include "RotateComponent.h"
#include "ObstacleManager.h"
#include "ObstacleObject.h"
#include "BikeObject.h"
#include "Math.h"

PlayerObject::PlayerObject()
	:GameObject()
{
    SetPosition(Vector3(0.0f, 0.0f, 60.0f));

    OBSTACLE_MANAGER->AddPlayer(this);
	rotate = new RotateComponent(this);

    moveComp = new MoveComponent(this);
    moveComp->SetRightKey(SDL_SCANCODE_RIGHT);
    moveComp->SetLeftKey(SDL_SCANCODE_LEFT);
    moveComp->SetMaxStrafeSpeed(2400.0f);
    autoRun = new AutoRunComponent(this);
    autoRun->SetForwardSpeed(2400.0f);
	camera = new MainCamera(this);
	camera->SnapToIdeal();

    dril = new BikeObject(this);
    autoRun->SetDrilObject(dril);

    SetScale(10.0f);

    tag = Tag::Player;
}

/**
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void PlayerObject::UpdateGameObject(float _deltaTime)
{
}

bool PlayerObject::CanMove()
{
    return rotate->CanMove();
}
