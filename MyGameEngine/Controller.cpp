#include "Controller.h"
#include"Engine/Camera.h"
#include "Engine/Input.h"

 Controller::Controller(GameObject* parent)
     :GameObject(parent, "Controller")
 {

     transform_.position_.x = 7.0f;
     transform_.position_.z = 7.0f;
     transform_.rotate_.x = 45.0f;
 }

 Controller::~Controller()
 {
 }

 void Controller::Initialize()
 {
 }

 void Controller::Update()
 {

     //左回転
     if (Input::IsKey(DIK_LEFT))
     {
         transform_.rotate_.y -= 1.0f;
     }

     //右回転
     if (Input::IsKey(DIK_RIGHT))
     {
         transform_.rotate_.y += 1.0f;
     }

     //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
     XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));


     //上回転
     if (Input::IsKey(DIK_UP))
     {
         transform_.rotate_.x += 1.0f;
         if (transform_.rotate_.x > 89)
         {
             transform_.rotate_.x = 89;
         }
     }

     //下回転
     if (Input::IsKey(DIK_DOWN))
     {
         transform_.rotate_.x -= 1.0f;
         if (transform_.rotate_.x < 0)
         {
             transform_.rotate_.x = 0;
         }

     }
     //回転行列
     XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
     
    //現在位置をベクトルにしておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //前後移動ベクトル
    XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);
    frontMove = XMVector3TransformCoord(frontMove, mRotateY);

        if (Input::IsKey(DIK_W))
        {
            vPos += frontMove;
        }
        if (Input::IsKey(DIK_S))
        {
            vPos -= frontMove;
        }
       
        //左右移動ベクトル
        XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);//右向きのXMVECTOR
        rightMove = XMVector3TransformCoord(rightMove, mRotateY);//移動ベクトル

        if (Input::IsKey(DIK_D))
        {
            vPos += rightMove;
        }
        if (Input::IsKey(DIK_A))
        {
            vPos -= rightMove;
        }
        XMStoreFloat3(&transform_.position_, vPos);

        //カメラ
        XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);     //自撮り棒用意
        vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);  //自撮り棒回転
        Camera::SetPosition(vPos + vCam);           //カメラの位置は自撮り棒の先端（現在地+自撮り棒）
        Camera::SetTarget(transform_.position_);    //カメラの見る位置はこのオブジェクトの位置
     
 }

 void Controller::Draw()
 {
 }

 void Controller::Release()
 {
 }
