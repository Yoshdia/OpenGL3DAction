#include "HeartParticleEffect.h"


/*
@param _pos 座標
@param _velocity 移動量
@param _broken 壊れたハートか。これを参照し生成する画像を変更する
*/
HeartParticleEffect::HeartParticleEffect(const Vector3& _pos, const Vector3& _velocity, const bool& broken):
	ParticleEffectBase(_pos,_velocity,30, broken==true?"Assets/Image/Effect/BrokenHeart.png":"Assets/Image/Effect/Heart.png",18)
{
}


HeartParticleEffect::~HeartParticleEffect()
{
}

/*
@fn velocity.xを一定値以下になるまで減少させ続ける
*/
void HeartParticleEffect::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
	if(velocity.x >= 0.2f||velocity.x<=-0.2f)
	{
		velocity.x /= 1.8f;
	}
	else
	{
		velocity.x = 0;
	}
}
