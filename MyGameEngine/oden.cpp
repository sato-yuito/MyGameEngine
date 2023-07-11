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
	this->transform_.position_.x = 0.2;
	this->transform_.position_.y = 0.2;
	this->transform_.position_.z = 0.2;


}

//�X�V
void oden::Update()
{
	this->transform_.rotate_.y++;
	
}

//�`��
void oden::Draw()
{
	pFbx->Draw(this->transform_);
}

//�J��
void oden::Release()
{
}