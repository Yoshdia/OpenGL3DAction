#pragma once
#include "ParticleEffectBase.h"

/*
@file ZoomingTransparencyEffect.h
@brief �g�債�Ȃ��瓧���x���オ���Ă����G�t�F�N�g
*/
class ZoomingTransparencyEffect :
	public ParticleEffectBase
{
public:
	/*
@param _pos ���W
*/
	ZoomingTransparencyEffect(const Vector3& _pos);
	~ZoomingTransparencyEffect();
private:
	/*
	@fn �摜�T�C�Y�𑫂������x���グ������
	*/
	void UpdateParticleObject(float _deltaTime)override;
	//�摜�T�C�Y
	float particleScale;
	//�摜�̓����x
	float particleAlfa;
};

