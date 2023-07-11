#include "GameObject.h"
#include "Direct3D.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
{
	objectName(name)
	{
		childList_.clear();
		state_ = { 0, 1, 1, 0 };

		if (parent)
			transform_.pParent_ = &parent->transform_;

	}

}

GameObject::~GameObject()
{
}

void GameObject::KillMe()
{
	state_.dead = 1;
}

bool GameObject::Isdead()
{
	return (state_.dead != 0);
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

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}

}

void GameObject::ReleaseSub()
{
}



void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();

	
}
