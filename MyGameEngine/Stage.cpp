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
int  Stage::GetBlock(int _x, int _z)
{
    return  table_[_x][_z].type;
}

int Stage::GetBlockHeght(int _x, int _z)
{
    return table_[_x][_z].height;
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

void Stage::Save()
{
    char fileName[MAX_PATH] = "����.map";  //�t�@�C����������ϐ�
    //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
    ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
    ofn.lpstrFile = fileName;               	//�t�@�C����
    ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
    ofn.lpstrDefExt = "map";                  	//�f�t�H���g�g���q
    //�u�t�@�C����ۑ��v�_�C�A���O
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);
    //�L�����Z�������璆�f
    if (selFile == FALSE) return;

    //�t�@�C���̍쐬
    HANDLE hFile = CreateFile
    (
        "SAVE.txt",               //�t�@�C����
        GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
        0,                      //���L�i�Ȃ��j
        NULL,                  //�Z�L�����e�B�����i�p�����Ȃ��j
        CREATE_ALWAYS,        //�쐬���@
        FILE_ATTRIBUTE_NORMAL,//�����ƃt���O�i�ݒ�Ȃ��j
        NULL                 //�g�������i�Ȃ��j
    );
    std::string WriteSaveFile;
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            WriteSaveFile += std::to_string(GetBlock(x,z)) + " " + std::to_string(GetBlockHeght(x, z)) + "";
        }
    }
    DWORD dwBytes = 0;  //�������݈ʒu
    //�t�@�C���̏�������
    WriteFile(
        hFile,                   //�t�@�C���n���h��
        WriteSaveFile.c_str(),                  //�ۑ�����f�[�^�i������j
        (DWORD)strlen(WriteSaveFile.c_str()),   //�������ޕ�����
        &dwBytes,                //�������񂾃T�C�Y������ϐ�
        NULL);                   //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j
    CloseHandle(hFile);
    //�t�@�C���̃T�C�Y���擾
    DWORD fileSize = GetFileSize(hFile, NULL);

    //�t�@�C���̃T�C�Y�����������m��
    char* data;
    data = new char[fileSize];
    //�t�@�C���̓ǂݍ���
    ReadFile(
        hFile,     //�t�@�C���n���h��
        data,      //�f�[�^������ϐ�
        fileSize,  //�ǂݍ��ރT�C�Y
        &dwBytes,  //�ǂݍ��񂾃T�C�Y
        NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j
    CloseHandle(hFile);
}

Stage*Stage::FindObject(string _filename)