#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"
class Enemy :
    public GameObject
{
    Fbx* pFbx;
    int hModel;
public:
    Enemy(GameObject* parent);

    ~Enemy();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release()override;

    //‰½‚©‚É“–‚½‚Á‚½
    //ˆø”FpTarget “–‚½‚Á‚½‘Šè
    void onCollision(GameObject* pTarget) override;
};

