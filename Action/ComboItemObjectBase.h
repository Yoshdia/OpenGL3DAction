#pragma once
#include "GameObject.h"
#include <unordered_map>

/*
@enum ComboItemName
�A�C�e���̖��O
*/
enum ComboItemName
{
	NoComboItem=-1,
	RotateComboItem=0,
	ThrowComboItem=1,
	HammerComboItem=2,
	SlashSwordComboItem=3,
};

/*
@file ComboItemObjectBase.h
@brief �v���C���[���擾����ƍU���N���X���擾����A�C�e���̊��N���X
*/
class ComboItemObjectBase :
	public GameObject
{
public:
	/*
	@param _pos ���W
	@param _name �A�C�e���̎��
	*/
	ComboItemObjectBase(const Vector3& _pos,const ComboItemName& _name);
	~ComboItemObjectBase();

	/*
	@fn ���􂵂ė�������
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn �I�u�W�F�N�gID�ł��̃I�u�W�F�N�g�̃A�C�e������������
	@param _objectID �I�u�W�F�N�gID
	@return ��������
	*/
	static ComboItemName SearchComboId(const int& _objectId);
private:
	//�I�u�W�F�N�gID���Ƃ̃A�C�e����
	static std::unordered_map<int,ComboItemName> comboItems;
	//�n�ʂ����m����N���X
	class SkeltonObjectChecker* noGround;
	//�ړ���
	Vector3 velocity;
};

