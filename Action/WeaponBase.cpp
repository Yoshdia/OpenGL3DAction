#include "WeaponBase.h"
#include "ColliderComponent.h"
#include "RotateComponent.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"

std::unordered_map<int, int> WeaponBase::weapons;

/*
@param _pos 座標
@param _waitCount 待機時間
@param _lifeCount 生存時間
@param _direction 向き
@param _tag タグ
@param _weaponName 武器の威力
@param _colliderSize 衝突範囲
@param _colorSub 白い色から元の色に戻るまでの速度
@param _meshFileName メッシュデータのアドレス
@param _skeletalFileName スケルトンデータのアドレス
*/
WeaponBase::WeaponBase(const Vector3 & _pos, const int & _waitCount, const int & _lifeCount, const float & _direction,
	const Tag& _tag, const int& _weaponName, const Vector3 & _colliderSize, const float& _colorSub, const std::string & _meshFileName, const char * _skeletalFileName) :
	GameObject(),
	waitCount(_waitCount),
	lifeCount(_lifeCount),
	activeCount(0),
	doCollision(true),
	color(1),
	colorSub(_colorSub)
{
	int dir = _direction == 1 ? 1 : -1;
	direction = dir;
	SetPosition(_pos);
	tag = _tag;
	rotateComponent = new RotateComponent(this);
	colliderComponent = new ColliderComponent(this, 100, _colliderSize, myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	colliderComponent->SetDoCollision(false);
	skeletalComponent = new SkeletalMeshComponent(this);
	if (_meshFileName != "none")
	{
		skeletalComponent->SetSkeleton(RENDERER->GetSkeleton(_skeletalFileName));
		skeletalComponent->SetMesh(RENDERER->GetMesh(_meshFileName));
	}
	skeletalComponent->SetVisible(false);
	if (tag == Tag::PlayerWeaponTag)
	{
		weapons.emplace(myObjectId, _weaponName);
	}
}

WeaponBase::~WeaponBase()
{
}

/*
@fn 元の色に戻す
*/
void WeaponBase::UpdateGameObject(float _deltaTime)
{
	//待機時間のカウント
	if (waitCount <= 0)
	{
		//色を変更
		skeletalComponent->SetColor(Vector3(color, color, color));
		//元の色に戻していく
		color -= colorSub;
		if (color > 1.0f)
		{
			color = 1.0f;
		}
		if (color < 0)
		{
			color = 0;
		}
		colliderComponent->SetDoCollision(true);
		skeletalComponent->SetVisible(true);
		UpdateWeaponGameObject(_deltaTime);
		activeCount++;
		if (lifeCount <= 0)
		{
			SetState(State::Dead);
		}
		else
		{
			lifeCount--;
		}
	}
	else
	{
		waitCount--;
	}
	if (doCollision)
	{
		colliderComponent->SetDoCollision(true);
	}
	else
	{
		colliderComponent->SetDoCollision(false);
	}
}

/*
@fn オブジェクトIDを基に威力を検索する
@param _objectId オブジェクトID
@return 威力
*/
int WeaponBase::SearchWeaponPower(const int & _objectId)
{
	auto iter = weapons.find(_objectId);
	if (iter != weapons.end())
	{
		int name = iter->second;
		return name;
	}
	return 0;
}
