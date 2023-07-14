#include "oden.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
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
	hModel = Model::Load("Assets/oden.fbx");
	assert(hModel >= 0);

	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;
}

//�X�V
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

//�`��
void oden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

//�J��
void oden::Release()
{
	
}