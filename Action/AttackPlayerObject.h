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
	float Attack(const float& _direction, const int& _slot, bool& _range);
private:
	void OnTriggerStay(ColliderComponent* _colliderPair) ;
	ComboItemObjectBase* DropComboItem(const ComboItemName& _name,const int& slot);
	void DeleteSlot(const int& _slot);

	static const Vector3 RightIconPos;
	static const Vector3 LeftIconPos;
	static const float IconSize;
	static const float BottonSize;

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
	class UserInterfaceBase* leftIcon;
	class UserInterfaceBase* rightIcon;
	class UserInterfaceBase* lButtonGuide;
	class UserInterfaceBase* lButtonIcon;
	class UserInterfaceBase* rButtonGuide;
	class UserInterfaceBase* rButtonIcon;
	bool itemCollided;
};

/*
���U���N���X�̒ǉ��菇
�@��⌕�̂悤�ȁA�e�X�̋����݂̂𐧌䂷�镐��N���X:GameObject���쐬
�A����N���X���󂯂Ƃ������W�A�����ɔ���������U���N���X:AttackBase���쐬
�B�U���N���X���R���{���Ƃɐ�������R���{�N���X:ComboMeanPlayerBase���쐬
~�t���ւ����s���ꍇ~
�CComboItemObjectBase���̗񋓌^�Ő錾
�D���̃N���XAttackPlayerObject���ł��̍U���N���X��t���ւ��邽�ߊ֐��ɕ��͂�������
*/
