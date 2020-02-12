#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"

/*
@param _pos オブジェクトの生成場所
@param _velocity オブジェクトの移動量
@param _lifeCount オブジェクトの生存時間
@param _spriteFileName 画像へのアドレス
@param _scale 画像の拡大サイズ
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
@fn 派生クラスの更新関数を呼び座標に移動量を足し続ける
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

/*
@fn 派生クラスごとに決定する更新関数
*/
void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

/*
@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
*/
void ParticleEffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
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
