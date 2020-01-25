#include "AttackPlayerObject.h"
#include "RotateTripleWeaponCombo.h"
#include "ThrowWeaponCombo.h"
#include "ColliderComponent.h"
#include "ComboItemObjectBase.h"
#include "DoubleHammerCombo.h"
#include "UserInterfaceBase.h"
#include "TakeItemEffectUI.h"

const Vector3 AttackPlayerObject::LeftIconPos = Vector3(300, -300, 0);
const Vector3 AttackPlayerObject::RightIconPos = Vector3(400, -300, 0);

AttackPlayerObject::AttackPlayerObject(GameObject* _owner) :
	GameObject(),
	owner(_owner),
	waitTimeForNextAttack(0),
	changeCount(0),
	itemCollided(false)
{
	firstSlotAttack = new RotateTripleWeaponCombo();
	leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName());
	leftIcon->SetScale(0.5f);
	secondSlotAttack = new ThrowWeaponCombo();
	rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName());
	rightIcon->SetScale(0.5f);


	UserInterfaceBase* xButton = new UserInterfaceBase(Vector3(300, -300, 0), "Assets/Image/UI/button_x.png", Vector3(0.3f, 0.3f, 0.3f), 1000);
	UserInterfaceBase* yButton = new UserInterfaceBase(Vector3(400, -300, 0), "Assets/Image/UI/button_y.png", Vector3(0.3f, 0.3f, 0.3f), 1000);
	tag = SubPlayerObject;

	lButtonGuide = new   UserInterfaceBase(Vector3(-25, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(0.3f, 0.3f, 0.3f), 500);
	lButtonGuide->SetState(State::Dead);
	rButtonGuide = new   UserInterfaceBase(Vector3(25, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(0.3f, 0.3f, 0.3f), 500);
	rButtonGuide->SetState(State::Dead);
	ColliderComponent* colliderPair = new ColliderComponent(this, 100, Vector3(30, 30, 30), gameObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
}

AttackPlayerObject::~AttackPlayerObject()
{
}

void AttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	SetPosition(owner->GetPosition());
	if (waitTimeForNextAttack < 0)
	{
		//コンボ状態をリセットする
		firstSlotAttack->ComboReset();
		secondSlotAttack->ComboReset();
	}
	else
	{
		waitTimeForNextAttack--;
	}
	if (changeCount >= 0)
	{
		changeCount--;
	}
	if (itemCollided)
	{
		lButtonGuide->SetState(State::Active);
		rButtonGuide->SetState(State::Active);
		itemCollided = false;
	}
	else
	{
		lButtonGuide->SetState(State::Dead);
		rButtonGuide->SetState(State::Dead);
	}
}

float AttackPlayerObject::Attack(const int& _direction, const int& _slot, bool& _range)
{
	float playerCanNotMoveTime = 0.0f;

	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			firstSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
			_range = firstSlotAttack->GetRangeFlag();
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			secondSlotAttack->Attack(owner->GetPosition(), _direction, playerCanNotMoveTime, waitTimeForNextAttack);
			_range = secondSlotAttack->GetRangeFlag();
		}
	}

	return playerCanNotMoveTime;
}

void AttackPlayerObject::OnTriggerStay(ColliderComponent* _colliderPair)
{
	if (_colliderPair->GetObjectTag() == Tag::ComboItem)
	{
		if (changeCount <= 0)
		{
			if (inputLeftChange || inputRightChange)
			{
				ComboItemName name = ComboItemObjectBase::SearchComboId(_colliderPair->GetId());
				if (inputLeftChange)
				{
					//設置されていたアイテムを非アクティブにする
					_colliderPair->GetOwner()->SetState(State::Dead);
					//現在所持しているクラスのアイテムをその場に置く
					firstSlotAttack->DropMyItem(position);
					//変更先クラスを取得する
					DropComboItem(name, 1);

				}
				else if (inputRightChange)
				{
					//設置されていたアイテムを非アクティブにする
					_colliderPair->GetOwner()->SetState(State::Dead);
					//現在所持しているクラスのアイテムをその場に置く
					secondSlotAttack->DropMyItem(position);
					//変更先クラスを取得する
					DropComboItem(name, 2);
				}
			}
		}
		itemCollided = true;

	}
}

ComboItemObjectBase* AttackPlayerObject::DropComboItem(const ComboItemName& _name, const int& _slot)
{
	changeCount = 25;
	switch (_name)
	{
	case(ComboItemName::RotateComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new RotateTripleWeaponCombo;
		}
		else
		{
			secondSlotAttack = new RotateTripleWeaponCombo;
		}
		break;
	case(ComboItemName::ThrowComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new ThrowWeaponCombo;
		}
		else
		{
			secondSlotAttack = new ThrowWeaponCombo;
		}
		break;
	case(ComboItemName::HammerComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new DoubleHammerCombo;
		}
		else
		{
			secondSlotAttack = new DoubleHammerCombo;
		}
		break;
	}
	if (_slot == 1)
	{
		leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName(),Vector3(1,1,1),100);
		leftIcon->SetScale(0.5f);
		new TakeItemEffectUI(LeftIconPos);
	}
	else
	{
		rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName());
		rightIcon->SetScale(0.5f);
		new TakeItemEffectUI(RightIconPos);
	}
	return nullptr;
}

void AttackPlayerObject::DeleteSlot(const int& _slot)
{
	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			delete firstSlotAttack;
		}
		if (leftIcon != nullptr)
		{
			delete leftIcon;
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			delete secondSlotAttack;
		}
		if (rightIcon != nullptr)
		{
			delete rightIcon;
		}
	}
}
