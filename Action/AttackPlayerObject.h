#pragma once
#include "GameObject.h"
#include "ComboItemObjectBase.h"

/*
@file AttackPlayerObject.h
@brief Player�ɋߐڃR���{�A�������U�����s�킹��N���X
*/
class AttackPlayerObject :
	public GameObject
{
public:
	AttackPlayerObject(GameObject* _owner);
	~AttackPlayerObject();
	void UpdateGameObject(float _deltaTime)override;
	void SetInput(const bool& _lInput, const bool& _rInput) { inputLeftChange = _lInput; inputRightChange =_rInput; }
	/*
	@fn �ߋ����U��
	@param _direction �U�����̃v���C���[�̌���
	@param _slot �U���X���b�g
	@param _range ���̃R���{���������U�����ǂ���
	@return �v���C���[�ɕt�^����s���s�Ȏ���
	*/
	float Attack(const int& _direction, const int& _slot, bool& _range);
private:
	void OnTriggerStay(ColliderComponent* _colliderPair) ;
	ComboItemObjectBase* DropComboItem(const ComboItemName& _name,const int& slot);
	void ChangeSlot(const int& _slot);

	bool inputLeftChange;
	bool inputRightChange;
	GameObject* owner;
	//���O�����s���U���X���b�g
	class ComboMeanPlayerBase* firstSlotAttack;
	//���O�����s���U���X���b�g
	class ComboMeanPlayerBase* secondSlotAttack;
	//�ߋ����U���̃R���{�����ɂȂ���P�\���ԁB���ꂪ0�ɂȂ�ƃR���{��Ԃ����Z�b�g����
	float waitTimeForNextAttack;

	int changeCount;
};

