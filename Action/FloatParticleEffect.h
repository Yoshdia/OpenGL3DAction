#pragma once
#include "ParticleEffectBase.h"

/*
@fn FloatParticleEffect.h
@brief ��������Ɛ^��ɏ㏸����
���̃N���X�͕K�v��������������Ȃ� ���N���X�Ɠ��e���ς���Ă��Ȃ�
*/
class FloatParticleEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos ���W
	@param _velocity �ړ���
	*/
	FloatParticleEffect(const Vector3& _pos, const Vector3& _velocity);
	~FloatParticleEffect();
private:
	void UpdateParticleObject(float _deltaTime)override;
};

