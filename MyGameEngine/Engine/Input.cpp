#include "Input.h"
namespace Input
{
	LPDIRECTINPUT8   pDInput_ = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;//�f�o�C�X�I�u�W�F�N�g
	BYTE keyState[256] ;//������Ă��邩�ǂ����̕ϐ���z��ŗp��
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	POINT mousePosition;

	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr; //�G���[�����p
		hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		hr = pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);//�f�o�C�X�I�u�W�F�N�g�̍쐬
		hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);//�f�o�C�X�̎�ނ��w��
		hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//�������x���̐ݒ�
		

		hr = pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		hr = pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		hr = pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		if (FAILED(hr))
		{
			MessageBox(NULL, "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
			
			return hr;
		}
	}

	//�L�[�̏�Ԃ��擾
	void Update()
	{
		memcpy(prevKeyState,keyState,sizeof(keyState));
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		//�}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	//����̃L�[�������ꂽ���ǂ���
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode]&0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode)&&!(prevKeyState[keyCode]&0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����Ă��Ȃ��đO��͉�����
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	///////�}�E�X���擾////////
	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	XMFLOAT3 GetMousePosition()
	{
		XMFLOAT3 result = XMFLOAT3((float)mousePosition.x, (float)mousePosition.y, 0);
		return result;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition.x = x;
		mousePosition.y = y;
	}

	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}
	void Release()
	{
		SAFE_RELEASE(pDInput_);
		SAFE_RELEASE(pKeyDevice);
	}
}