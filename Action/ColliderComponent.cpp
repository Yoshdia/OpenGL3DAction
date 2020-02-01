#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsWorld.h"

/*
@fn GameObject����󂯎�����֐��|�C���^��ۑ���PhysicsWorld�Ɏ�����ǉ�
@param owner �eGameObject�ւ̃|�C���^
@param updateOrder ����Component�̍X�V����
@param size �����蔻��̃T�C�Y(GameObject��Scale�Ƃ͈قȂ�)
@param objectId GameObject�ɐU����ÓI�Ȏ��ʔԍ�
@param tag GameObject�ɐU����ÓI�ȗ񋓌^
@param colliderPos �Փ˔��肪���݂��钆�S���W�@�eGameObject�̍��W�ɑ����Ďg�p����
 */
ColliderComponent::ColliderComponent(GameObject * owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)>TriggerEnter, std::function<void(ColliderComponent*)> TriggerStay, Tag tag, Vector3 colliderPos) :
	Component(owner, updateOrder)
	, size(size)
	, colliderPos(colliderPos)
	, doCollision(true)
	, collidedCamera(false)
{
	OnTriggerEnter = TriggerEnter;
	OnTriggerStay = TriggerStay;
	PhysicsWorld::GetInstance()->AddCollider(this);
}

/*
@fn PhysicsWorld���玩�����폜
*/
ColliderComponent::~ColliderComponent()
{
	PhysicsWorld::GetInstance()->RemoveCollider(this);
}

/*
@fn Collider�N���X�ɂĐeObject���Փ˂�����Ăяo�����
@fn �Փˑ���̎��ʎq�Ƒ���Ƃ̏Փˏ�Ԃ��L������
@param colliderParter �Փˑ����ColliderComponent
@detail Collider�N���X�ŐeObject���Փ˂������Ƃ�`�����A
	  �Փˏ�Ԃ�OF�ŏՓ˂��Ă����Փˏ��Ŕ��f���L������֐�
*/
void ColliderComponent::OnCollision(ColliderComponent* colliderParter)
{
	CollisionState state = CollisionState::Enter;
	//�OF�œ����I�u�W�F�N�g�ƐڐG���Ă����ꍇState��Stay�֕ύX������
	for (auto obj : beforeCollisions)
	{
		if (obj.first->GetId() == colliderParter->GetId())
		{
			state = CollisionState::Stay;
			break;
		}
	}
	//auto iter = hadCollision.find(colliderParter);
	//if (iter != hadCollision.end())
	//{
	//	state = CollisionState::Stay;
	//}
	//��F�ŐڐG���Ă��郊�X�g�ɑ}��
	nowCollisions.emplace_back(std::make_pair(colliderParter, state));
	//isCollision.emplace(colliderParter, state);
}

/*
@fn ��F�X�V�����֐�
@fn ���ݐڐG���Ă��郊�X�g��O�t���[���ڐG���Ă������X�g�ֈڂ��Ȃǂ͂����ōs��
*/
void ColliderComponent::Update(float deltaTime)
{
	CollisionReaction(deltaTime);

	beforeCollisions.clear();
	beforeCollisions = nowCollisions;
	nowCollisions.clear();
	//hadCollision.clear();
	//hadCollision = isCollision;
	//isCollision.clear();
	//�Փ˂��s����
	if (doCollision)
	{
		//��F�ňړ����s������(�ړ����s���Ă��Ȃ��̂ɏՓ˂��邱�Ƃ͖�������)
		if (owner->GetRecomputeWorldTransform())
		{
			PhysicsWorld::GetInstance()->Collision(this);
		}
		//PhysicsWorld::Collision()�ŃJ�����̏Փ˔͈͂ɐڐG������;
		if (!collidedCamera)
		{
			//�ڐG���Ă��Ȃ���ʊO�ƂȂ�X�V����~����
			owner->SetState(State::Paused);
		}
		else
		{
			//�ڐG�����ꍇ�X�V���ĊJ����
			if (owner->GetTag() != Tag::Camera)
			{
				collidedCamera = false;
			}
		}
	}
}

/*
@fn �ڐG�����I�u�W�F�N�g�B�Ƃ̐ڐG��Ԃ����ƂɐeGameObject�̃��A�N�V�����֐��ɐڐG�����Tag��n��
*/
void ColliderComponent::CollisionReaction(float deltaTime)
{
	//�ڐG�����I�u�W�F�N�g�B�Ƃ̐ڐG��Ԃ����ƂɐeGameObject�̃��A�N�V�����֐��ɐڐG�����Tag��n��
	for (auto obj : nowCollisions)
	{
		switch (obj.second)
		{
		case(CollisionState::Enter):
			OnTriggerEnter(obj.first);
			OnTriggerStay(obj.first);
			break;
		case(CollisionState::Stay):
			OnTriggerStay(obj.first);

			break;
		}
	}
}

/*
@fn �eObject�̍��W��Ԃ�
*/
Vector3 ColliderComponent::GetPosition()
{
	return owner->GetPosition() + colliderPos;
}

/*
@fn �eObject�̎��ʔԍ���Ԃ�
*/
int ColliderComponent::GetId()
{
	return owner->GetObjectId();
}

/*
@fn �e�I�u�W�F�N�g�̃^�O
*/
Tag ColliderComponent::GetObjectTag()
{
	return owner->GetTag();
}

/*
@fn �e�I�u�W�F�N�g�̏��
*/
State ColliderComponent::GetState()
{
	return owner->GetState();
}


