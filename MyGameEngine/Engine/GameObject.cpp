#include "GameObject.h"
#include "Direct3D.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),dead_(false)
{
	if (pParent_ )
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::KillMe()
{
	dead_ = true;
}

void GameObject::Initialize()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

void GameObject::Release()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->UpdateSub();

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->dead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
	
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	Release();
}


GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		//自分が_objNameのオブジェクトだったら
		return(this);
	}
	else
	{
		for (auto itr:childList_)
		{
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// 再起呼び出しでRootJobを探してそのアドレスを返す関数
/// </summary>
/// <returns>RootJobのアドレス(GameObject *型)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}
