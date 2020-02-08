#include "HeartParticleEffect.h"


/*
@param _pos ���W
@param _velocity �ړ���
@param _broken ��ꂽ�n�[�g���B������Q�Ƃ���������摜��ύX����
*/
HeartParticleEffect::HeartParticleEffect(const Vector3& _pos, const Vector3& _velocity, const bool& broken):
	ParticleEffectBase(_pos,_velocity,30, broken==true?"Assets/Image/Effect/BrokenHeart.png":"Assets/Image/Effect/Heart.png",18)
{
}


HeartParticleEffect::~HeartParticleEffect()
{
}

/*
@fn velocity.x�����l�ȉ��ɂȂ�܂Ō�������������
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
