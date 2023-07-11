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
	
}

//�X�V
void Player::Update()
{
	this->transform_.rotate_.y ++;
	if (Input::IsKey(DIK_ESCAPE))
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