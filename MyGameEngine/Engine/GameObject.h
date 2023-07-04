#pragma once

#include "Transform.h"
#include ""
#include 

class GameObject
{
	œœœœœœœœ childList_;
	Transform	transform_;
	œœœœœœ	pParent_;
	œœœœœœ	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() œœœ;
	virtual void Update() œœœ;
	virtual void Draw() œœœ;
	virtual void Release() œœœ;
};

