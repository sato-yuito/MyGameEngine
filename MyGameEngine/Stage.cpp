#include "Stage.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_MAX; i++)
    {
        hModel_[i] = -1;
    }

    for (int x = 0; x < width_; x++)
    {
        for (int z = 0; z < height_; z++)
        {
            table_[x][z] = 0;
        }
    }
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    string modelname[] =
    {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string fname_base = "assets/";
    //���f���f�[�^�̃��[�h
        for (int i = 0; i < MODEL_MAX; i++)
        {
            hModel_[i] = Model::Load(fname_base+modelname[i]);
            assert(hModel_[i] >= 0);
        }
        for (int z = 0; z < height_; z++)
        {
            for (int x = 0; x < width_; x++)
            {
                table_[x][z] = x % 5;
            }
         }
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    //Model::SetTransform(hModel_, transform_);
    //Model::Draw(hModel_);
    Transform blockTrans;
    int type = 0;
    for (int x = 0; x < width_; x++)
    {
        for (int z = 0; z < height_; z++)
        {
            blockTrans.position_.x = x;
            blockTrans.position_.z = z;

            type = table_[x][z];
            Model::SetTransform(hModel_[type], blockTrans);
            Model::Draw(hModel_[type]);
        }
    }
}

//�J��
void Stage::Release()
{
}
