#pragma once
#include "ParticleEffectBase.h"

/*
 @file HeartParticleEffect.h
 @brief �n�[�g�̉摜���㏸������G�t�F�N�g
*/
class HeartParticleEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos ���W
	@param _velocity �ړ���
	@param _broken ��ꂽ�n�[�g���B������Q�Ƃ���������摜��ύX����
	*/
	HeartParticleEffect(const Vector3& _pos, const Vector3& _velocity,const bool& broken=false);
	~HeartParticleEffect();
private:
	/*
	@fn velocity.x�����l�ȉ��ɂȂ�܂Ō�������������
	*/
	void UpdateParticleObject(float _deltaTime)override;
};

