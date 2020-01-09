#pragma once
#include "Component.h"

/*
@file AttackPlayerComponent.h
@brief Playerに近接コンボ、遠距離攻撃を行わせるクラス
*/
class AttackPlayerComponent :
	public Component
{
public:
	AttackPlayerComponent(GameObject* _owner, int _updateOrder);
	~AttackPlayerComponent();

	void Update(float _deltaTime);

	/*
	@fn 近距離攻撃
	@param _direction 攻撃時のプレイヤーの向き
	@param _slot 攻撃スロット
	@param _range このコンボが遠距離攻撃かどうか
	@return プレイヤーに付与する行動不可な時間
	*/
	float Attack(const int& _direction,const int& _slot,bool& _range);
private:
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* firstSlotAttack;
	//つけ外しを行う攻撃スロット
	class ComboMeanPlayerBase* secondSlotAttack;
	//近距離攻撃のコンボを次につなげる猶予時間。これが0になるとコンボ状態をリセットする
	float waitTimeForNextAttack;
};

