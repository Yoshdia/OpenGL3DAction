#include "ShieldWeapon.h"
#include "ColliderComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"

const int ShieldWeapon::ActiveCount = 30;
const float ShieldWeapon::CreatedHeightShield = 100;
const int ShieldWeapon::FloatingCount = 15;

ShieldWeapon::ShieldWeapon(std::function<void(const int&)> _AddGuardingObjectIdFunc) :
	GameObject(),
	activeCount(0),
	floatingCount(0)
{
	tag = (Tag::PlayerGuardWeaponTag);
	AddGuardingObjectIdFunc = _AddGuardingObjectIdFunc;
	SetState(State::Dead);

	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));
}

ShieldWeapon::~ShieldWeapon()
{
}

void ShieldWeapon::UpdateGameObject(float _deltaTime)
{
	//���V�J�E���g����
	if (floatingCount <= 0)
	{
		//�����ς݂�
		if (position.y >= targetHeight)
		{
			//�ڕW�n�_�܂ŗ���
			Vector3 pos = position;
			pos.y -= 12.0f;;
			SetPosition(pos);
		}
		else
		{
			//�A�N�e�B�u���ԓ���
			if (activeCount <= 0)
			{
				SetState(State::Dead);
			}
			else
			{
				activeCount--;
			}
		}
	}
	else
	{
		floatingCount--;
	}
}

void ShieldWeapon::CreateShield(const Vector3& _pos)
{
	//���W�̃Z�b�g
	SetState(State::Active);
	Vector3 pos = _pos;
	pos.y += CreatedHeightShield;
	SetPosition(pos);
	//�e�J�E���g�̃��Z�b�g
	activeCount = ActiveCount;
	floatingCount = FloatingCount;
	targetHeight = _pos.y;
}

void ShieldWeapon::OnTriggerStay(ColliderComponent* _colliderPair)
{
	if (_colliderPair->GetObjectTag() == Tag::EnemyWeaponTag)
	{
		AddGuardingObjectIdFunc(_colliderPair->GetId());
	}
}
