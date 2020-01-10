#include "ComboItemObjectBase.h"
#include "ColliderComponent.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "SkeltonObjectChecker.h"

std::unordered_map<int, ComboItemName> ComboItemObjectBase::comboItems;

ComboItemObjectBase::ComboItemObjectBase(const Vector3 & _pos, const std::string& _fileName, const ComboItemName& _name) :
	GameObject()
{
	SetPosition(_pos);
	tag = Tag::ComboItem;
	ColliderComponent* colliderPair = new ColliderComponent(this, 100, Vector3(30, 30, 30), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag);
	ParticleComponent*par = new ParticleComponent(this);
	par->SetScale(50);
	if (_name == ComboItemName::HammerComboItem)
	{
		par->SetColor(Vector3(1, 0, 0));
	}
	par->SetTextureID(RENDERER->GetTexture(_fileName)->GetTextureID());
	noGround = new SkeltonObjectChecker(this, Vector3(0, -15, 0), Vector3(5, 1, 5), Tag::GroundTag);
	comboItems.emplace(myObjectId,_name);
}

ComboItemObjectBase::~ComboItemObjectBase()
{
}

void ComboItemObjectBase::UpdateGameObject(float _deltaTime)
{
}

ComboItemName ComboItemObjectBase::SearchComboId(const int & _objectId)
{
	auto iter = comboItems.find(_objectId);
	if (iter != comboItems.end())
	{
		ComboItemName name = iter->second;
		return name;
	}
	return ComboItemName::NoComboItem;
}
