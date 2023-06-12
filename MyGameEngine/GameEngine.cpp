#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
#include"Dice.h"
#include"Camera.h"

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const char* MENU_BAR_NAME = "Let's make game";
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{  
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
   WNDCLASSEX wc;
   wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
   wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
   wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
   wc.lpszMenuName = MENU_BAR_NAME;
   wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
   wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
   wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
   wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
   wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
   RegisterClassEx(&wc);  //�N���X��o�^

    //�E�B���h�E�T�C�Y�̌v�Z
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //�E�B���h�E��
    int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

    //�E�B���h�E���쐬
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //�E�B���h�E�N���X��
        MENU_BAR_NAME,     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW , //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,              //�E�B���h�E��
        winH,        //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        hInstance,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );
    //�E�B���h�E��\��
    ShowWindow(hWnd, nCmdShow);

    //Direct3D������
    HRESULT hr;
    hr =Direct3D::Initialize(winW, winH, hWnd);
    if (FAILED(hr))
    {
        PostQuitMessage(0);  //�v���O�����I��
    }

    Camera::Initialize();
    //Quad�֐�������
   // Quad* quad = new Quad;
    Dice* dice = new Dice;
    //hr = quad->Initialize();
    hr = dice->Initialize();
    if (FAILED(hr))
    {
        PostQuitMessage(0);  //�v���O�����I��
    }

  

    //���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
            Camera::Update();
            //�Q�[���̏���
            Direct3D::BeginDraw();
           
            //�`�揈��
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
            XMMATRIX mat = XMMatrixRotationX(XMConvertToRadians(a));   //X����30����]������s��
            //XMMATRIX matY = XMMatrixRotationY(XMConvertToRadians(b));   //Y����30����]������s��
            //XMMATRIX matZ= XMMatrixRotationZ(XMConvertToRadians(c));   //Z����30����]������s��
            //XMMATRIX mat = matZ*matX*matY;//�񂷊|���Z
            //XMMATRIX matB = XMMatrixTranslation(4, 0, 0);
            //XMMATRIX mat = matA * matB;
            //quad->Draw(mat);
            dice->Draw(mat);
            Direct3D::EndDraw();
        }
    }

    //�������
    //SAFE_DELETE(quad);
    SAFE_DELETE(dice);
    Direct3D::Release();
   
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)//���O�͉��ł�����
{
    switch (msg)
    {
    
    case WM_DESTROY:
    PostQuitMessage(0);  //�v���O�����I��
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}