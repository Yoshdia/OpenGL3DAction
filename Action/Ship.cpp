#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"

/**
@param	�Q�[���N���X�̃|�C���^
*/
Ship::Ship()
	:GameObject()
{
	//SpriteComponent* sprite = new SpriteComponent(this,100);
	//sprite->SetTexture(game->GetTexture("Assets/Ship.png"));
}

Ship::~Ship()
{
}

/**
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void Ship::UpdateGameObject(float _deltaTime)
{
}
