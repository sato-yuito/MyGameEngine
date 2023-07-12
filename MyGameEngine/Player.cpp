#include "Player.h"
#include"Engine/Input.h"
#include"oden.h"
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
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	Instantiate<oden>(this);
	GameObject*pCO2 = Instantiate<oden>(this);
	pCO2->SetPosition(-2, 1, 0);
}

//�X�V
void Player::Update()
{
	transform_.rotate_.y ++;
	if (transform_.rotate_.y > 600)
	{
		KillMe();
    }
}

//�`��
void Player::Draw()
{
	pFbx->Draw(this->transform_);
}

//�J��
void Player::Release()
{
}