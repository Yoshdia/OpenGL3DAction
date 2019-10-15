#include "Ship.h"
#include "SpriteComponent.h"
#include "Renderer.h"
/**
@param	ゲームクラスのポインタ
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
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void Ship::UpdateGameObject(float _deltaTime)
{
}
