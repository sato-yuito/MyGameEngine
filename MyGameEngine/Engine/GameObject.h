#pragma once

#include"Transform.h"
#include <list>
#include <string>

class GameObject
{
protected:
	std::list<GameObject*>	childList_;
	Transform				transform_;
	GameObject*				pParent_;
	std::string				objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize()	= 0;
	virtual void Update()  = 0;
	virtual void Draw()  = 0;
	virtual void Release()  = 0;

	template <class T>
	void Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		childList_.push_back(p);
	}
	void KillMe();
	bool Isdead();
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();
	
};

