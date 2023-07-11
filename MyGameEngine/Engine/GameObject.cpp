#include "GameObject.h"
#include "Direct3D.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
{
	

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
