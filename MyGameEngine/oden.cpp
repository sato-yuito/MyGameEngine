#include "oden.h"
#include"Engine/Input.h"

//�R���X�g���N�^
oden::oden(GameObject* parent)
	:GameObject(parent, "oden"), pFbx(nullptr)
{
}

//�f�X�g���N�^
oden::~oden()
{
}

//������
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

//�X�V
void oden::Update()
{
	this->transform_.rotate_.y++;
	if (transform_.rotate_.y > 300)
		KillMe();
}

//�`��
void oden::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void oden::Release()
{
}