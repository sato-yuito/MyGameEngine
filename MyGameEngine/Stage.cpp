#include "Stage.h"
#include "Engine/Model.h"
#include"resource.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
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
        /*for (int z = 0; z < height_; z++)
        {
            for (int x = 0; x < width_; x++)
            {
                SetBlock(x, z, (BLOCKTYPE)(z % 5));
                SetBlockHeght(x, z,x%4);
            }
         }*/
}

//�X�V
void Stage::Update()
{
    float w = (float)(scrWidth /2.0f );
    float h = (float)(scrHeight /2.0f );
    int inX = -1;//x���W������ϐ���
    int inZ = -1;//z���W������ϐ���
    float distance = -1;//����������
    if (!Input::IsMouseButtonDown(0))
    {
        return;
    }
    XMMATRIX vp =
    {
        w, 0, 0,0,
        0,-h, 0,0,
        0, 0, 1,0,
        w, h, 0,1
    };
    //�r���[�|�[�g
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj = XMMatrixInverse(nullptr ,Camera::GetProjectionMatrix());
    //�r���[�ϊ�
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
    //mousePosFront���x�N�g���ɕϊ�
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //vMouseFront�ɏ�O��������
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //mousePosBack���x�N�g���ɕϊ�
    XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
    //vMousePosBack�ɏ�O��������
    vMousePosBack = XMVector3TransformCoord(vMousePosBack, invVP * invProj * invView);

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir,vMousePosBack -vMouseFront);
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[0], trans);

                Model::RayCast(hModel_[0], data);

                if (data.hit)
                {
                    if (distance > data.dist|| distance == -1)
                        //�}�E�X���N���b�N�����ꏊ������I������
                    {
                        inX = x;
                        inZ = z;
                        distance = data.dist;
                    }
                    break;
                }
                
            }
           
        }
       
    }
    switch (mode_)
    {
    case(up):
        table_[inX][inZ].height++;
        break;
    case(down):
        if (table_[inX][inZ].height > 0)
            table_[inX][inZ].height--;
        break;
    case(change):
        SetBlock(inX,inZ, (BLOCKTYPE)select_);
    }
    
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

    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case IDC_COMBO1:
            select_ = static_cast<int>(SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0));
            break;
        case IDC_RADIO_UP:
            mode_ = up;
            break;
        case IDC_RADIO_down:
            mode_ = down;
            break;
        case IDC_RADIO3:
            mode_ = change;
            break;
        }
       
    }
    return FALSE;
}
