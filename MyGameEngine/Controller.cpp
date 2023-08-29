#include "Controller.h"
#include"Engine/Camera.h"
#include "Engine/Input.h"

 Controller::Controller(GameObject* parent)
 {
 }

 Controller::~Controller()
 {
 }

 void Controller::Initialize()
 {
 }

 void Controller::Update()
 {
     //現在の位置情報を取得
     XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

     //1フレームの移動量（ベクトル）
     XMVECTOR vMove = { 0.0f, 0.0f, 0.1f, 0.0f };     //奥方向に0.1m

     //transform_.rotate_.y度回転させる行列
     XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

     //移動ベクトルを変形（コントローラーの向いている方向）
     vMove = XMVector3TransformCoord(vMove, mRotY);


     Camera::SetTarget(transform_.position_);
     XMVECTOR vCam = { 0, 5, 15, 0 };
     vCam = XMVector3TransformCoord(vCam, mRotY);
     XMFLOAT3 camPos;
     XMStoreFloat3(&camPos, vPos + vCam);
     Camera::SetPosition(camPos);

     //移動処理
     if (Input::IsKey(DIK_W))
     {
         vPos -= vMove;                              //移動
         XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
     }
     if (Input::IsKey(DIK_S))
     {
         vPos += vMove;                              //移動
         XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
     }

     if (Input::IsKey(DIK_D))
     {
         transform_.position_.x -= 0.5f;
     }
     if (Input::IsKey(DIK_A))
     {
         transform_.position_.x += 0.5f;

     }
     if (Input::IsKey(DIK_LEFT))
     {
         transform_.rotate_.y -= 0.8f;
     }
     if (Input::IsKey(DIK_RIGHT))
     {
         transform_.rotate_.y += 2.0f;
     }

 }

 void Controller::Draw()
 {
 }

 void Controller::Release()
 {
 }
