#pragma once
#include "ParticleEffectBase.h"

/*
@file DamageSquareEffect.h
@brief �g�債�Ȃ��瓧���x���オ���Ă����G�t�F�N�g
�G�̔�e���Ɏg�p���邽�߂ɂ��̖��O�ɂ������A�p�r���ς�������߉����̕K�v����B
*/
class DamageSquareEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos ���W
	*/
	DamageSquareEffect(const Vector3& _pos);
	~DamageSquareEffect();
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

