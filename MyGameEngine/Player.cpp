#include "Player.h"


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),pFbx(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
}

//更新
void Player::Update()
{
	this->transform_.rotate_.y += 1;
}

//描画
void Player::Draw()
{
	pFbx->Draw(this->transform_);
}

//開放
void Player::Release()
{
}