#pragma once
#include "Engine/GameObject.h"
#include"Engine/Fbx.h"
class oden :
    public GameObject
{
    Fbx* pFbx;
public:
    //�R���X�g���N�^
    oden(GameObject* parent);

    //�f�X�g���N�^
    ~oden();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};


