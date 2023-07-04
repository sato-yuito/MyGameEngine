#pragma once

#include "Transform.h"
#include ""
#include 

class GameObject
{
	���������������� childList_;
	Transform	transform_;
	������������	pParent_;
	������������	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() ������;
	virtual void Update() ������;
	virtual void Draw() ������;
	virtual void Release() ������;
};

