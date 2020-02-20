#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "PlayerCharacter.h"

PhysicsWorld* PhysicsWorld::physicsWorld = nullptr;

/*
@fn PhysicsWorld����
*/
void PhysicsWorld::CreateInstance()
{
	if (!physicsWorld)
	{
		physicsWorld = new PhysicsWorld();
	}
}

/*
@fn PhysicsWorld���
*/
void PhysicsWorld::DeleteInstance()
{
	delete physicsWorld;
	physicsWorld = nullptr;
}

/*
@fn �������ꂽColliderComponent��colliders�֒ǉ�
@param _collider PhysicsWorld�N���X�ɒǉ��������N���X
*/
void PhysicsWorld::AddCollider(ColliderComponent* _collider)
{
	colliders.emplace_back(_collider);
}

/*
�@@fn ��������Ă���ColliuderComponent��colliders����폜
 @param _collider PhysicsWorld�N���X�������������N���X
*/
void PhysicsWorld::RemoveCollider(ColliderComponent* _collider)
{
	auto iter = std::find(colliders.begin(), colliders.end(), _collider);
	if (iter != colliders.end())
	{
		std::iter_swap(iter, colliders.end() - 1);
		colliders.pop_back();
	}
}

/*
@fn �Փ˔���
@param _collider �Փ˂��s���AColliderComponent����Ă΂��Փˊ֐�
*/
void PhysicsWorld::Collision(ColliderComponent* _collider)
{
	Tag obj1Tag = _collider->GetObjectTag();
	for (auto collider2 : colliders)
	{
		Tag obj2Tag = collider2->GetObjectTag();
		//�I�u�W�F�N�g���Ƃ̗񋓌^���r���Փ˂̗D�揇�ʂ��ƂɏՓ˂��s��
		if (obj1Tag < obj2Tag)
		{
			if (_collider->GetObjectTag() != Tag::Camera)
			{
				if (collider2->GetState() == State::Paused)
				{
					continue;
				}
			}
			//�Փˌv�Z���肪���X�V��ԂłȂ���
			if (collider2->GetState() == State::Dead)
			{
				continue;
			}
			//�Փ˗\�葊�肪�Փ˂��s����
			if (!collider2->GetDoCollision())
			{
				continue;
			}

			//�Փ˂�����
			int hit = false;

			AABB obj1(_collider->GetPosition(), _collider->GetCollisionSize());
			AABB obj2(collider2->GetPosition(), collider2->GetCollisionSize());

			hit = Intersect(obj1, obj2);

			//�Փ˂��Ă�����
			if (hit > 0)
			{
				//�J�������Փ˂�������ł��OF�܂ŉ�ʊO�|�[�Y�������I�u�W�F�N�g������������
				if (obj1Tag == Tag::Camera)
				{
					if (obj2Tag != Tag::ParticleEffectTag)
					{
						collider2->SetCollidedCamera();
						if (collider2->GetState() == State::Paused)
						{
							collider2->GetOwner()->SetState(State::Active);
						}
					}
				}

				//�v���C���[�A�G�l�~�[�͒n�ʂƂ̂߂荞�ݕ␳���s���v���C���[�͔����Ƃ߂荞�ݕ␳���s��
				if (obj1Tag == Tag::PlayerTag && obj2Tag == Tag::GroundTag ||
					obj1Tag == Tag::EnemyTag && obj2Tag == Tag::GroundTag ||
					obj1Tag == Tag::PlayerTag && obj2Tag == Tag::ThinGroundFloor)
				{
					_collider->GetOwner()->FixCollision(obj1, obj2, obj2Tag);
				}
				else if (obj1Tag == Tag::GroundTag && obj2Tag == Tag::ParticleEffectTag)
				{
					collider2->GetOwner()->FixCollision(obj1, obj2, obj2Tag);
				}

				_collider->OnCollision(collider2);
				collider2->OnCollision(_collider);
			}
		}
		else
		{
			continue;
		}

	}
}

/*
@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
@param _movableBox �ړ�����
@param _fixedBox �ړ����Ȃ�����
@param _calcFixVec �ړ����̂̕␳�����x�N�g��
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, z�̂����ł��������������ňʒu�𒲐�
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
