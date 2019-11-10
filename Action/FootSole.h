#pragma once
#include "GameObject.h"

/*
 @file FootSole.h
 @brief GameObjectの足元に配置するパネル状のオブジェクト、groundTagを所持しているオブジェクトに接触するとフラグを倒す
	*/
class FootSole :
	public GameObject
{
public:
	/*
   @param parentPosition 親になるオブジェクトの座標アドレス
   @param _jumped 親になるオブジェクトのジャンプフラグアドレス。FootSoleがgroundTagと接触したときにfalseにする
 */
	FootSole(GameObject* _parent);
	~FootSole();

	void UpdateGameObject(float _deltaTime)override;

	bool GetGroundFlag() { return noGround; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair)override;
	GameObject* parent;
	Vector3 parentPos;
	//自信の座標、parentPositionと足しでpositionにする
	Vector3 footPos;
	bool noGround;
};

