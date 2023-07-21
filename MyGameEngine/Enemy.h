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

    //何かに当たった
    //引数：pTarget 当たった相手
    void onCollision(GameObject* pTarget) override;
};

