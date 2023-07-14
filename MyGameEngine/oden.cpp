#include "oden.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
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
	hModel = Model::Load("Assets/oden.fbx");
	assert(hModel >= 0);

	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;
}

//更新
void oden::Update()
{
	this->transform_.rotate_.y++;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 50)
	{
		KillMe();
	}
	/*if (transform_.rotate_.y > 300)
		KillMe();*/
}

//描画
void oden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

//開放
void oden::Release()
{
	
}