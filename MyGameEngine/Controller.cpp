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
     //���݂̈ʒu�����擾
     XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

     //1�t���[���̈ړ��ʁi�x�N�g���j
     XMVECTOR vMove = { 0.0f, 0.0f, 0.1f, 0.0f };     //��������0.1m

     //transform_.rotate_.y�x��]������s��
     XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

     //�ړ��x�N�g����ό`�i�R���g���[���[�̌����Ă�������j
     vMove = XMVector3TransformCoord(vMove, mRotY);


     Camera::SetTarget(transform_.position_);
     XMVECTOR vCam = { 0, 5, 15, 0 };
     vCam = XMVector3TransformCoord(vCam, mRotY);
     XMFLOAT3 camPos;
     XMStoreFloat3(&camPos, vPos + vCam);
     Camera::SetPosition(camPos);

     //�ړ�����
     if (Input::IsKey(DIK_W))
     {
         vPos -= vMove;                              //�ړ�
         XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
     }
     if (Input::IsKey(DIK_S))
     {
         vPos += vMove;                              //�ړ�
         XMStoreFloat3(&transform_.position_, vPos); //���݈ʒu�̍X�V
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
