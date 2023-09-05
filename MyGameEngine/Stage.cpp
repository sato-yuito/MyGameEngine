#include "Stage.h"
#include "Engine/Model.h"
#include"resource.h"

void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeght(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}

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
            SetBlock(x, z, DEFAULT);
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
                SetBlock(x, z, (BLOCKTYPE)(z % 5));
                SetBlockHeght(x, z,x%4);
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
    for (int x = 0; x < width_; x++)
    {
        for (int z = 0; z < height_; z++)
        {
            for (int y = 0; y < table_[x][z].height+1; y++)
            {
                int  type = table_[x][z].type;
                Transform blockTrans;
                blockTrans.position_.x = x;
                blockTrans.position_.y = y;
                blockTrans.position_.z = z;
                
              
                Model::SetTransform(hModel_[type], blockTrans);
                Model::Draw(hModel_[type]);
            }
        }
    }
   
}

//�J��
void Stage::Release()
{
}

//�X�e�[�W�̃_�C�A���O
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        //���W�I�{�^���̏����l
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
        
        //�R���{�{�b�N�X�̏����l
   
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("�f�t�H���g"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("�����K"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
        return true;
    }
    return FALSE;
}
