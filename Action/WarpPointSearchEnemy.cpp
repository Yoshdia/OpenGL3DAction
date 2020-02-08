#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"

/*
@param _pos ���W
*/
WarpPointSearchEnemy::WarpPointSearchEnemy(Vector3 _pos) :
	GameObject(),
	searchedPoint(true),
	moveDirection(MoveDirection::left),
	isGround(false)
{
	footGroundChecker = new SkeltonObjectChecker(this, Vector3(0, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardGroundChecker = new SkeltonObjectChecker(this, Vector3((float)moveDirection * 50.0f, -75, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardWallChecker = new SkeltonObjectChecker(this, Vector3((float)moveDirection * 50.0f, 30, 0), Vector3(1, 1, 1), Tag::GroundTag);
}

WarpPointSearchEnemy::~WarpPointSearchEnemy()
{
}

void WarpPointSearchEnemy::UpdateGameObject(float _deltaTime)
{
	//�������I�����Ă��Ȃ���
	if (!searchedPoint)
	{
		//�n�ʂ��������I������
		if (!footGroundChecker->GetNoTouchingFlag() || isGround)
		{
		
			SetPosition(position + Vector3((float)(moveDirection * 5), 0, 0));
			//�i�s�����ɕǂ�����B���͐i�s�����̉��ɏ��������Ƃ��������I������
			if (forwardGroundChecker->GetNoTouchingFlag() || !forwardWallChecker->GetNoTouchingFlag())
			{
				searchedPoint = true;
				printf("Searched Position! \n");
			}
			isGround = true;
		}
		else
		{
			SetPosition(position + Vector3(0, -1.0f * 6.0f, 0));
		}
	}
	else
	{
		SetPosition(Vector3::Zero);
	}
}
/*
@fn ���W�̌������J�n����
@brief �n�ʂ�����������ɍ��E�ǂ��炩�ɐi�ނ����肷��
@param _position �����J�n�n�_
@param _enemyPosition ���̃I�u�W�F�N�g���g�p���Ă���G�l�~�[�̍��W
*/
void WarpPointSearchEnemy::SetFirstPosition(Vector3 _position, Vector3 _enemyPosition)
{
	searchedPoint = false;
	isGround = false;
	SetPosition(_position);
	float x = _position.x - _enemyPosition.x;
	if (x > 0)
	{
		moveDirection = MoveDirection::left;
	}
	else
	{
		moveDirection = MoveDirection::right;
	}
	forwardGroundChecker->SetOffset(Vector3((float)moveDirection * 50.0f, -75, 0));
	forwardGroundChecker->SetPosition(_position);
	forwardWallChecker->SetOffset(Vector3((float)moveDirection * 50.0f, 30, 0));
	forwardWallChecker->SetPosition(_position);
	footGroundChecker->SetPosition(Vector3(0, 0, 0) + position);
	printf("Search Start %f.%f\n", position.x, position.y);
	}
