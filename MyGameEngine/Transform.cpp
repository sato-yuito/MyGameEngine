#include "Transform.h"

Transform::Transform()
{
    //移動、回転、拡大の初期化
    position_ = XMFLOAT3(0, 0, 0);
    rotate_ = XMFLOAT3(0, 0, 0);
    scale_ = XMFLOAT3(1, 1, 1);

    //移動、回転、拡大それぞれの行列の初期化
    matTranslate_ = XMMatrixIdentity();
    matRotate_ = XMMatrixIdentity();
    matScale_ = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //移動行列
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
    //回転行列
    XMMATRIX rotate_X, rotate_Y, rotate_Z;
    rotate_X = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    rotate_Y = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    rotate_Z = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = rotate_Z * rotate_X * rotate_Y;
    //回転行列
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    Calclation();
    return matScale_* matRotate_* matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
    return 
}
