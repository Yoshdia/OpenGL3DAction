#pragma once
#include "GameObject.h"
#include "ComboItemObjectBase.h"

/*
@file AttackPlayerObject.h
@brief Playerに近接コンボ、遠距離攻撃を行わせるクラス
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
	@fn 近距離攻撃
	@param _direction 攻撃時のプレイヤーの向き
	@param _slot 攻撃スロット
	@param _range このコンボが遠距離攻撃かどうか
	@return プレイヤーに付与する行動不可な時間
	*/
	float Attack(const int& _direction, const int& _slot, bool& _range);
private:
	void OnTriggerStay(ColliderComponent* _colliderPair) ;
	ComboItemObjectBase* DropComboItem(const ComboItemName& _name,const int& slot);
	void ChangeSlot(const int& _slot);

	bool inputLeftChange;
	bool inputRightChange;
	GameObject* owner;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* firstSlotAttack;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* secondSlotAttack;
	//近距離攻撃のコンボを次につなげる猶予時間。これが0になるとコンボ状態をリセットする
	float waitTimeForNextAttack;

	int changeCount;
};

