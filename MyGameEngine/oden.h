#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"
class oden :
    public GameObject
{
    Fbx* pFbx;
public:
    //コンストラクタ
    oden(GameObject* parent);

    //デストラクタ
    ~oden();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};


