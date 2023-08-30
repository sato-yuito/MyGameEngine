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

struct BLOCK
{
    BLOCKTYPE type;
    int height;
};
//Stage���Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[MODEL_MAX];    //���f���ԍ�
    BLOCK table_[width_] [height_];
  
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeght(int _x, int _z, int _height);
};

