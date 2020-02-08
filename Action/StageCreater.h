#pragma once
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file StageCreater.h
@brief �X�e�[�W�f�[�^��ǂݍ��݃X�e�[�W�𐶐�����
*/
class StageCreater :
	public GameObject
{
public:
	StageCreater();
	~StageCreater();
	/*
	@fn �t�@�C�����J��
	@return �������ۂ�
	*/
	bool OpenFile();
	/*
	@fn �v���C���[�𐶐�����
	*/
	class PlayerCharacter* CreatePlayer();
	/*
	@fn �X�e�[�W�𐶐�����
	*/
	void CreateStage();
	/*
	@fn �Փ˂��s��Ȃ��w�i�𐶐�����
	*/
	void CreateBackGround();

private:
	/*
	@fn Json�t�@�C����ǂݍ��݃R���e�i�^�Ɋi�[����
	@param _mapDate �i�[���������R���e�i�ւ̃A�h���X
	@param _fileName Json�t�@�C���A�h���X
	@param _layerName Json�t�@�C�����̃��C���[�A�h���X
	@return false=���s
	*/
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);
	// �X�e�[�W�f�[�^
	std::vector<std::vector<int>> mapData;
	//�z�u����I�u�W�F�N�g�̊ԊuX
	int sizeX;
	//�z�u����I�u�W�F�N�g�̊ԊuY
	int sizeY;
	//�w�i�f�[�^0
	std::vector<std::vector<int>> backData0;
	//�z�u����I�u�W�F�N�g�̊Ԋu�B�T�C�Y
	float offset;
	//�{�X�I�u�W�F�N�g�ւ̃|�C���^
	class GameObject* bossEnemy;
public://�Q�b�^�[�Z�b�^�[
		/*
	@return �{�X�ւ̃A�h���X
	*/
	class GameObject* GetBossEnemy() { return bossEnemy; }
};

