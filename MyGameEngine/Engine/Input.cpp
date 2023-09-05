#include "Input.h"
namespace Input
{
	LPDIRECTINPUT8   pDInput_ = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;//デバイスオブジェクト
	BYTE keyState[256] ;//押されているかどうかの変数を配列で用意
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//デバイスオブジェクト
	DIMOUSESTATE mouseState_;				//マウスの状態
	DIMOUSESTATE prevMouseState_;			//前フレームのマウスの状態
	POINT mousePosition;

	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr; //エラー処理用
		hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		hr = pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);//デバイスオブジェクトの作成
		hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);//デバイスの種類を指定
		hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//強調レベルの設定
		

		hr = pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		hr = pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		hr = pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		if (FAILED(hr))
		{
			MessageBox(NULL, "デバイスオブジェクトの作成に失敗しました", "エラー", MB_OK);
			
			return hr;
		}
	}

	//キーの状態を取得
	void Update()
	{
		memcpy(prevKeyState,keyState,sizeof(keyState));
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		//マウス
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	//特定のキーが押されたかどうか
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
		//今は押してて、前回は押してない
		if (IsKey(keyCode)&&!(prevKeyState[keyCode]&0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//今は押していなくて前回は押した
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	///////マウス情報取得////////
	bool IsMouseButton(int buttonCode)
	{
		//押してる
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
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