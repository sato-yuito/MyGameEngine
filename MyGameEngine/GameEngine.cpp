#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
#include"Dice.h"
#include"Camera.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* MENU_BAR_NAME = "Let's make game";
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{  
	//ウィンドウクラス（設計図）を作成
   WNDCLASSEX wc;
   wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
   wc.hInstance = hInstance;                   //インスタンスハンドル
   wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
   wc.lpszMenuName = MENU_BAR_NAME;
   wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
   wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
   wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
   wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
   wc.lpszMenuName = NULL;                     //メニュー（なし）
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
   RegisterClassEx(&wc);  //クラスを登録

    //ウィンドウサイズの計算
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

    //ウィンドウを作成
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //ウィンドウクラス名
        MENU_BAR_NAME,     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW , //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,       //表示位置左（おまかせ）
        CW_USEDEFAULT,       //表示位置上（おまかせ）
        winW,              //ウィンドウ幅
        winH,        //ウィンドウ高さ
        NULL,                //親ウインドウ（なし）
        NULL,                //メニュー（なし）
        hInstance,           //インスタンス
        NULL                 //パラメータ（なし）
    );
    //ウィンドウを表示
    ShowWindow(hWnd, nCmdShow);

    //Direct3D初期化
    HRESULT hr;
    hr =Direct3D::Initialize(winW, winH, hWnd);
    if (FAILED(hr))
    {
        PostQuitMessage(0);  //プログラム終了
    }

    Camera::Initialize();
    //Quad関数初期化
   // Quad* quad = new Quad;
    Dice* dice = new Dice;
    //hr = quad->Initialize();
    hr = dice->Initialize();
    if (FAILED(hr))
    {
        PostQuitMessage(0);  //プログラム終了
    }

  

    //メッセージループ（何か起きるのを待つ）
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
            Camera::Update();
            //ゲームの処理
            Direct3D::BeginDraw();
           
            //描画処理
            //XMMATRIX matA = XMMatrixRotationZ(XMConvertToRadians(45));
            //XMMATRIX matB = XMMatrixTranslation(4, 0, 0);
            //XMMATRIX matC = XMMatrixScaling(1, 3, 1);
            //XMMATRIX mat = matC * matA * matB;
            static int a = 0;
            //static int b = 0;
            //static int c = 0;
            a += 1;
            //b += 1;
            //c += 1;
            XMMATRIX mat = XMMatrixRotationX(XMConvertToRadians(a));   //X軸で30°回転させる行列
            //XMMATRIX matY = XMMatrixRotationY(XMConvertToRadians(b));   //Y軸で30°回転させる行列
            //XMMATRIX matZ= XMMatrixRotationZ(XMConvertToRadians(c));   //Z軸で30°回転させる行列
            //XMMATRIX mat = matZ*matX*matY;//回す掛け算
            //XMMATRIX matB = XMMatrixTranslation(4, 0, 0);
            //XMMATRIX mat = matA * matB;
            //quad->Draw(mat);
            dice->Draw(mat);
            Direct3D::EndDraw();
        }
    }

    //解放処理
    //SAFE_DELETE(quad);
    SAFE_DELETE(dice);
    Direct3D::Release();
   
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)//名前は何でもいい
{
    switch (msg)
    {
    
    case WM_DESTROY:
    PostQuitMessage(0);  //プログラム終了
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}