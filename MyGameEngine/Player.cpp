#include "Player.h"
#include"Engine/Input.h"
#include"oden.h"
#include"Engine/Model.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),pFbx(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	hModel_ = Model::Load("Assets/oden.fbx");
	assert(hModel_ >= 0);
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	/*Instantiate<oden>(this);
	GameObject*pCO2 = Instantiate<oden>(this);
	pCO2->SetPosition(-2, 1, 0);*/
}

//�X�V
void Player::Update()
{
	transform_.rotate_.y ++;
	/*if (transform_.rotate_.y > 600)
	{
		KillMe();
    }*/
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject*pBallet = Instantiate<oden>(pParent_);
		pBallet->SetPosition(transform_.position_);
	}
}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}