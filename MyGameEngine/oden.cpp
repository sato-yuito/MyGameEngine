#include "oden.h"
#include"Engine/Input.h"

//コンストラクタ
oden::oden(GameObject* parent)
	:GameObject(parent, "oden"), pFbx(nullptr)
{
}

//デストラクタ
oden::~oden()
{
}

//初期化
void oden::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;
	transform_.position_.x = 2.0f;
	transform_.position_.y = 1.0f;
}

//更新
void oden::Update()
{
	this->transform_.rotate_.y++;
	if (transform_.rotate_.y > 300)
		KillMe();
}

//描画
void oden::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void oden::Release()
{
}