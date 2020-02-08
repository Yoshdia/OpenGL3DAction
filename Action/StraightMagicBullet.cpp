#include "StraightMagicBullet.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ParticleComponent.h"
#include "Texture.h"

/*
@param _shotPosition 座標
@param _targetPosition 目標座標
@param _waitCount 待機時間
*/
StraightMagicBullet::StraightMagicBullet(const Vector3 & _shotPosition, const Vector3 & _targetPosition, const int & _waitCount) :
	WeaponBase(_shotPosition, _waitCount, 150, 1, Tag::EnemyWeaponTag, 1, Vector3(10, 10, 10),1, "none", "none")
{
	force = Vector3::Normalize(_targetPosition - _shotPosition);
	ParticleComponent* particle= new ParticleComponent(this);
	particle->SetTextureID(RENDERER->GetTexture("Assets/Image/EnemyShot.png")->GetTextureID());
	particle->SetVisible(true);
	particle->SetScale(30.0f);
}

StraightMagicBullet::~StraightMagicBullet()
{
}

/*
@fn 力の方向へ進行する
*/
void StraightMagicBullet::UpdateWeaponGameObject(float _deltaTime)
{
	SetPosition(position + (force * 4));
}
