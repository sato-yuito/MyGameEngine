#pragma once
#include "Engine/GameObject.h"

namespace {
    const int MODEL_MAX{ 5 };
    const int width_{ 15 };
    const int height_{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT,BRICK,GRASS,SAND,WATER
    };
};


//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[MODEL_MAX];    //モデル番号
    int table_[width_] [height_];
    
public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

