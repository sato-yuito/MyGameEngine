#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"
class Player :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;
public:
    //�R���X�g���N�^
   Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

