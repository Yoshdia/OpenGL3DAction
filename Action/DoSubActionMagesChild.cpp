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
	//�e�I�u�W�F�N�g��ǐ�
	SetPosition(owner->GetPosition());
	//�ǂ��炩�̖��߂����Ă�����
	if (floating || droppingDown)
	{
		//�e�I�u�W�F�N�g�̍��W
		Vector3 ownerPos = owner->GetPosition();
		if (floating)
		{
			//targetHeight�܂ŕ���
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
			//�n�ʂ����m����܂ŗ���
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
