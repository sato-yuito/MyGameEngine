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
	this->transform_.position_.x = 0.2;
	this->transform_.position_.y = 0.2;
	this->transform_.position_.z = 0.2;


}

//更新
void oden::Update()
{
	this->transform_.rotate_.y++;
	
}

//描画
void oden::Draw()
{
	pFbx->Draw(this->transform_);
}

//開放
void oden::Release()
{
}