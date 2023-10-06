#pragma once
#include "Engine/GameObject.h"
#include<Windows.h>
#include"Engine/Direct3D.h"

using namespace Direct3D;
namespace {
    const int MODEL_MAX{ 5 };
    const int width_{ 15 };
    const int height_{ 15 };
    
    enum BLOCKTYPE
    {
        DEFAULT,BRICK,GRASS,SAND,WATER
    };
   
};

struct BLOCK
{
    BLOCKTYPE type;
    
    int height;
};
enum Mode
{
    up,
    down,
    change,
    keep,
};
//Stageを管理するクラス
class Stage : public GameObject
{
    int hModel_[MODEL_MAX];    //モデル番号
    BLOCK table_[width_] [height_];
  
    Mode mode_;
    int select_;
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

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeght(int _x, int _z, int _height);
    int GetBlock(int _x, int _z);
    int GetBlockHeght(int _x, int _z);
};

