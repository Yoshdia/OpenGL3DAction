#pragma once
#include "GameObject.h"
#include <unordered_map>

enum ComboItemName
{
	NoComboItem=-1,
	RotateComboItem=0,
	ThrowComboItem=1,
	HammerComboItem=2,
	SlashSwordComboItem=3,
};

class ComboItemObjectBase :
	public GameObject
{
public:
	ComboItemObjectBase(const Vector3& _pos,const ComboItemName& _name);
	~ComboItemObjectBase();

	void UpdateGameObject(float _deltaTime)override;
	static ComboItemName SearchComboId(const int& _objectId);
private:
	static std::unordered_map<int,ComboItemName> comboItems;
	class SkeltonObjectChecker* noGround;
	Vector3 velocity;
};

