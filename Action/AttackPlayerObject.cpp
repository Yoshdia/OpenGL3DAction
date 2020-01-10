#include "AttackPlayerObject.h"
#include "RotateTripleWeaponCombo.h"
#include "ThrowWeaponCombo.h"
#include "ColliderComponent.h"
#include "ComboItemObjectBase.h"
#include "DoubleHammerCombo.h"

AttackPlayerObject::AttackPlayerObject(GameObject * _owner) :
	GameObject(),
	owner(_owner),
	waitTimeForNextAttack(0),
	changeCount(0)
{
	firstSlotAttack = new RotateTripleWeaponCombo();
	secondSlotAttack = new ThrowWeaponCombo();
	tag = SubPlayerObject;
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
		//�R���{��Ԃ����Z�b�g����
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
}

float AttackPlayerObject::Attack(const int & _direction, const int & _slot, bool & _range)
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

void AttackPlayerObject::OnTriggerStay(ColliderComponent * _colliderPair)
{
	if (_colliderPair->GetObjectTag() == Tag::ComboItem)
	{
		ComboItemName name = ComboItemObjectBase::SearchComboId(_colliderPair->GetId());
		if (changeCount <= 0)
		{
			if (inputLeftChange)
			{
				//�ݒu����Ă����A�C�e�����A�N�e�B�u�ɂ���
				_colliderPair->GetOwner()->SetState(State::Dead);
				//���ݏ������Ă���N���X�̃A�C�e�������̏�ɒu��
				firstSlotAttack->DropMyItem(position);
				//�ύX��N���X���擾����
				DropComboItem(name, 1);
			}
			else if (inputRightChange)
			{
				//�ݒu����Ă����A�C�e�����A�N�e�B�u�ɂ���
				_colliderPair->GetOwner()->SetState(State::Dead);
				//���ݏ������Ă���N���X�̃A�C�e�������̏�ɒu��
				secondSlotAttack->DropMyItem(position);
				//�ύX��N���X���擾����
				DropComboItem(name, 2);
			}
		}
	}
}

ComboItemObjectBase * AttackPlayerObject::DropComboItem(const ComboItemName & _name, const int& _slot)
{
	changeCount = 50;
	switch (_name)
	{
	case(ComboItemName::RotateComboItem):
		ChangeSlot(_slot);
		if (_slot==1)
		{
			firstSlotAttack = new RotateTripleWeaponCombo;
		}
		else
		{
			secondSlotAttack = new RotateTripleWeaponCombo;
		}
		break;
	case(ComboItemName::ThrowComboItem):
		ChangeSlot(_slot);
		if (_slot==1)
		{
			firstSlotAttack = new ThrowWeaponCombo;
		}
		else
		{
			secondSlotAttack = new ThrowWeaponCombo;
		}
		break;
	case(ComboItemName::HammerComboItem):
		ChangeSlot(_slot);
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
	return nullptr;
}

void AttackPlayerObject::ChangeSlot(const int & _slot)
{
	if (_slot == 1)
	{
		if (firstSlotAttack != nullptr)
		{
			delete firstSlotAttack;
		}
	}
	else
	{
		if (secondSlotAttack != nullptr)
		{
			delete secondSlotAttack;
		}
	}
}
