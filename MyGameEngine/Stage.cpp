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



//コンストラクタ
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

//デストラクタ
Stage::~Stage()
{
}

//初期化
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
    //モデルデータのロード
        for (int i = 0; i < MODEL_MAX; i++)
        {
            hModel_[i] = Model::Load(fname_base+modelname[i]);
            assert(hModel_[i] >= 0);
        }
   
}

//更新
void Stage::Update()
{
    float w = (float)(scrWidth /2.0f );
    float h = (float)(scrHeight /2.0f );
    int inX = -1;//x座標を入れる変数名
    int inZ = -1;//z座標を入れる変数名
    float distance = -1;//距離を入れる
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
    //ビューポート
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //プロジェクション変換
    XMMATRIX invProj = XMMatrixInverse(nullptr ,Camera::GetProjectionMatrix());
    //ビュー変換
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;
    //mousePosFrontをベクトルに変換
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //vMouseFrontに上三つをかける
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    //mousePosBackをベクトルに変換
    XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
    //vMousePosBackに上三つをかける
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
                        //マウスをクリックした場所だけを選択する
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

//描画
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

//開放
void Stage::Release()
{
}

//ステージのダイアログ
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        //ラジオボタンの初期値
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg,IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
        
        //コンボボックスの初期値
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("デフォルト"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("レンガ"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("草"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("砂"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, LPARAM("水"));
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
    char fileName[MAX_PATH] = "無題.map";  //ファイル名を入れる変数
    //「ファイルを保存」ダイアログの設定
    OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
        TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
    ofn.lpstrFile = fileName;               	//ファイル名
    ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
    ofn.lpstrDefExt = "map";                  	//デフォルト拡張子
    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);
    //キャンセルしたら中断
    if (selFile == FALSE) return;

    //ファイルの作成
    HANDLE hFile = CreateFile
    (
        "SAVE.txt",               //ファイル名
        GENERIC_WRITE,           //アクセスモード（書き込み用）
        0,                      //共有（なし）
        NULL,                  //セキュリティ属性（継承しない）
        CREATE_ALWAYS,        //作成方法
        FILE_ATTRIBUTE_NORMAL,//属性とフラグ（設定なし）
        NULL                 //拡張属性（なし）
    );
    std::string WriteSaveFile;
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            WriteSaveFile += std::to_string(GetBlock(x,z)) + " " + std::to_string(GetBlockHeght(x, z)) + "";
        }
    }
    DWORD dwBytes = 0;  //書き込み位置
    //ファイルの書き込み
    WriteFile(
        hFile,                   //ファイルハンドル
        WriteSaveFile.c_str(),                  //保存するデータ（文字列）
        (DWORD)strlen(WriteSaveFile.c_str()),   //書き込む文字数
        &dwBytes,                //書き込んだサイズを入れる変数
        NULL);                   //オーバーラップド構造体（今回は使わない）
    CloseHandle(hFile);
    //ファイルのサイズを取得
    DWORD fileSize = GetFileSize(hFile, NULL);

    //ファイルのサイズ分メモリを確保
    char* data;
    data = new char[fileSize];
    //ファイルの読み込み
    ReadFile(
        hFile,     //ファイルハンドル
        data,      //データを入れる変数
        fileSize,  //読み込むサイズ
        &dwBytes,  //読み込んだサイズ
        NULL);     //オーバーラップド構造体（今回は使わない）
    CloseHandle(hFile);
}

Stage*Stage::FindObject(string _filename)