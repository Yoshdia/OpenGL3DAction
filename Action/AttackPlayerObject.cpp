#include "AttackPlayerObject.h"
#include "RotateTripleWeaponCombo.h"
#include "ThrowWeaponCombo.h"
#include "ColliderComponent.h"
#include "ComboItemObjectBase.h"
#include "DoubleHammerCombo.h"
#include "UserInterfaceBase.h"
#include "TakeItemEffectUI.h"
#include "TripleSlashSwordCombo.h"
#include "TakeItemUi.h"

const Vector3 AttackPlayerObject::LeftIconPos = Vector3(300, -400, 0);
const Vector3 AttackPlayerObject::RightIconPos = Vector3(500, -400, 0);
const float AttackPlayerObject::IconSize = 0.85;
const float AttackPlayerObject::BottonSize = 0.3f;

/*
@param _owner �e�I�u�W�F�N�g
*/
AttackPlayerObject::AttackPlayerObject(GameObject* _owner) :
	GameObject(),
	owner(_owner),
	waitTimeForNextAttack(0),
	changeCount(0),
	itemCollided(false)
{
	firstSlotAttack = new RotateTripleWeaponCombo();
	leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName());
	leftIcon->SetScale(IconSize);
	secondSlotAttack = new RotateTripleWeaponCombo();
	rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName());
	rightIcon->SetScale(IconSize);


	UserInterfaceBase* xButton = new UserInterfaceBase(LeftIconPos, "Assets/Image/UI/button_x.png", Vector3(BottonSize, BottonSize, BottonSize), 1000);
	UserInterfaceBase* yButton = new UserInterfaceBase(RightIconPos, "Assets/Image/UI/button_y.png", Vector3(BottonSize, BottonSize, BottonSize), 1000);
	tag = SubPlayerObject;

	lButtonIcon = new   UserInterfaceBase(LeftIconPos + Vector3(0, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(BottonSize, BottonSize, BottonSize), 550);
	lButtonGuide = new   UserInterfaceBase(Vector3(-25, 50, 0), "Assets/Image/UI/bumper1_l1.png", Vector3(BottonSize, BottonSize, BottonSize), 500);
	lButtonGuide->SetState(State::Dead);
	rButtonIcon = new   UserInterfaceBase(RightIconPos + Vector3(0, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(BottonSize, BottonSize, BottonSize), 550);
	rButtonGuide = new   UserInterfaceBase(Vector3(25, 50, 0), "Assets/Image/UI/bumper1_r1.png", Vector3(BottonSize, BottonSize, BottonSize), 500);
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

/*
@fn �ߋ����U��
@param _direction �U�����̃v���C���[�̌���
@param _slot �U���X���b�g
@param _range ���̃R���{���������U�����ǂ���
@return �v���C���[�ɕt�^����s���s�Ȏ���
*/
float AttackPlayerObject::Attack(const float& _direction, const int& _slot, bool& _range)
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
					//�ݒu����Ă����A�C�e�����A�N�e�B�u�ɂ���
					_colliderPair->GetOwner()->SetState(State::Dead);
					//���ݏ������Ă���N���X�̃A�C�e�������̏�ɒu��
					firstSlotAttack->DropMyItem(position);
					//�ύX��N���X���擾����
					DropComboItem(name, 1);
					new TakeItemUi(Vector3(0, 0, 0), LeftIconPos, firstSlotAttack->GetComboIconFileName(), Vector3(0.8f, 0.8f, 0.8f));
				}
				else if (inputRightChange)
				{
					//�ݒu����Ă����A�C�e�����A�N�e�B�u�ɂ���
					_colliderPair->GetOwner()->SetState(State::Dead);
					//���ݏ������Ă���N���X�̃A�C�e�������̏�ɒu��
					secondSlotAttack->DropMyItem(position);
					//�ύX��N���X���擾����
					DropComboItem(name, 2);
					new TakeItemUi(Vector3(0, 0, 0), RightIconPos, secondSlotAttack->GetComboIconFileName(), Vector3(0.8f, 0.8f, 0.8f));
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
	case(ComboItemName::SlashSwordComboItem):
		DeleteSlot(_slot);
		if (_slot == 1)
		{
			firstSlotAttack = new TripleSlashSwordCombo;
		}
		else
		{
			secondSlotAttack = new TripleSlashSwordCombo;
		}
		break;
	}
	if (_slot == 1)
	{
		leftIcon = new UserInterfaceBase(LeftIconPos, firstSlotAttack->GetComboIconFileName(), Vector3(IconSize, IconSize, IconSize), 150);
		new TakeItemEffectUI(LeftIconPos);
	}
	else
	{
		rightIcon = new UserInterfaceBase(RightIconPos, secondSlotAttack->GetComboIconFileName(), Vector3(IconSize, IconSize, IconSize), 150);
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
