#include "Ship.h"
#include "SpriteComponent.h"
#include "Renderer.h"
/**
@param	�Q�[���N���X�̃|�C���^
*/
Ship::Ship()
	:GameObject()
{
	spriteComponent = new SpriteComponent(this, 100);
	//spriteComponent->SetTexture(Renderer::GetInstance()->GetTexture("Assets/Image/once.png"));
	printf("%5f,%5f,%5f", position.x, position.y, position.z);
	SetPosition(Vector3(0, 0, 10));
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
