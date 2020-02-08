#include "BoneAnimationBaseComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"

/*
@fn メッシュデータクラスを確保
*/
BoneAnimationBaseComponent::BoneAnimationBaseComponent(GameObject * _owner, int updateOrder) :
	Component(_owner,updateOrder),
	startFlash(false),
	flashColor(0),
	plusFlashColor(false)
{
	skeltalMeshComponent = new SkeletalMeshComponent(_owner);
}

BoneAnimationBaseComponent::~BoneAnimationBaseComponent()
{
}

/*
 @fn 派生クラスで決定する関数と発光関数Flash()を更新する
*/
void BoneAnimationBaseComponent::Update(float _deltaTime)
{
	Flash();
	UpdateAnimationComponent(_deltaTime);
}

/*
 @fn 発光を行うフラグが建っているとき、メッシュカラーを増減させメッシュデータに色情報を渡す
*/
void BoneAnimationBaseComponent::Flash()
{
	//発光を行うか
	if (startFlash)
	{
		//色を白へ増加中か
		if (plusFlashColor)
		{
			//白になるまで色を増やし白になったらフラグを倒す
			if (flashColor > 1.0f)
			{
				flashColor = 1.0f;
				plusFlashColor = false;
			}
			else
			{
				flashColor += 0.2f;
			}
		}
		else
		{
			//色が0になるまで減少させる
			if (flashColor < 0)
			{
				flashColor = 0;
				startFlash = false;
			}
			else
			{
				flashColor -= 0.2f;
			}
		}
		//メッシュデータに色を送る
		skeltalMeshComponent->SetColor(Vector3(flashColor, flashColor, flashColor));
	}
}
