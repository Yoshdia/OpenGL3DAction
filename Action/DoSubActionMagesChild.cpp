#include "DoSubActionMagesChild.h"
#include "SkeltonObjectChecker.h"

const float DoSubActionMagesChild::FloatHeight = 150;
const float DoSubActionMagesChild::FloatSpeed = 10;
const float DoSubActionMagesChild::DroppingSpeed = -10;

DoSubActionMagesChild::DoSubActionMagesChild(GameObject* _owner) :
	GameObject(),
	targetHeight(0),
	floating(false),
	droppingDown(false)
{
	owner = _owner;
	footChcker = new SkeltonObjectChecker(this, Vector3(0, -5, 0), Vector3(8, 10, 1), Tag::GroundTag);
}

DoSubActionMagesChild::~DoSubActionMagesChild()
{
}

void DoSubActionMagesChild::UpdateGameObject(float _deltaTime)
{
	//親オブジェクトを追跡
	SetPosition(owner->GetPosition());
	//どちらかの命令が来ていたか
	if (floating || droppingDown)
	{
		//親オブジェクトの座標
		Vector3 ownerPos = owner->GetPosition();
		if (floating)
		{
			//targetHeightまで浮上
			droppingDown = false;
			if (ownerPos.y <= targetHeight)
			{
				owner->SetPosition(ownerPos += Vector3(0, FloatSpeed, 0));
			}
			else
			{
				floating = false;
			}
		}
		if (droppingDown)
		{
			//地面を検知するまで落下
			floating = false;
			if (footChcker->GetNoTouchingFlag())
			{
				owner->SetPosition(ownerPos + Vector3(0, DroppingSpeed, 0));
			}
			else
			{
				droppingDown = false;
			}
		}
	}
}

void DoSubActionMagesChild::StartFloating()
{
	floating = true;
	targetHeight = owner->GetPosition().y + FloatHeight;
}

void DoSubActionMagesChild::StartDroppingDown()
{
	droppingDown = true;
}
