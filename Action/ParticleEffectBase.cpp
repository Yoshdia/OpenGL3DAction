#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"

/*
@param _pos �I�u�W�F�N�g�̐����ꏊ
@param _velocity �I�u�W�F�N�g�̈ړ���
@param _lifeCount �I�u�W�F�N�g�̐�������
@param _spriteFileName �摜�ւ̃A�h���X
@param _scale �摜�̊g��T�C�Y
*/
ParticleEffectBase::ParticleEffectBase(const Vector3 & _pos, const Vector3 & _velocity,const int& _lifeCount, const std::string& _spriteFileName, const float& _scale):
	GameObject(),
	lifeCount(_lifeCount),
	velocity(_velocity)
{
	SetPosition(_pos);
	particleComponent = new ParticleComponent(this);
	particleComponent->SetTextureID(RENDERER->GetTexture(_spriteFileName)->GetTextureID());
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particleComponent->SetScale(_scale);
}

ParticleEffectBase::~ParticleEffectBase()
{
}

/*
@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

/*
@fn �h���N���X���ƂɌ��肷��X�V�֐�
*/
void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

/*
@fn �������Ԃ��J�E���g�_�E������֐��B�h���N���X�ōX�V�֐������肵���ꍇ�����ɒǉ����邱�ƁB
*/
void ParticleEffectBase::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (lifeCount <= 0)
	{
		particleComponent->SetVisible(false);
		SetState(State::Dead);
	}
	else
	{
		particleComponent->SetVisible(true);
		lifeCount--;
	}
}

void ParticleEffectBase::SetReverve(float _flag)
{
	particleComponent->SetReverce(_flag);
}
