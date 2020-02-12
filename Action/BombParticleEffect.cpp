#include "BombParticleEffect.h"
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

/*
@param _pos 座標
@param _velocity 移動量
*/
BombParticleEffect::BombParticleEffect(const Vector3& _pos, const Vector3& _velocity) :
	ParticleEffectBase(_pos, _velocity, 70, "Assets/Image/16.png")
{
	tag = (Tag::ParticleEffectTag);
	 col = new ColliderComponent(this, 100, Vector3(40, 40, 40), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);

}


BombParticleEffect::~BombParticleEffect()
{
}

/*
@fn 画面が静止しているときに残り続けないようカウントダウンを続ける
*/
void BombParticleEffect::PausingUpdateGameObject()
{
	LifeCountDown();
	col->SetCollidedCamera();
}

/*
@fn 地面と衝突したときにvelocity.yを反転させvelocity.xを減少させる
*/
void BombParticleEffect::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::GroundTag)
	{
		velocity.y *= -1;
		velocity = velocity * 0.8f;
	}
}

/*
@fn 重力を反映させる
*/
void BombParticleEffect::UpdateParticleObject(float _deltaTime)
{
	velocity.y -= 100 * _deltaTime;
	LifeCountDown();
}
