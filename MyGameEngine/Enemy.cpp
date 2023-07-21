#include "Enemy.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	transform_.position_.z = 30.0f;
	assert(hModel >= 0);

	SphereCollider* collision = new SphereCollider(1.0f);
	AddCollider(collision);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}

//‰½‚©‚É“–‚½‚Á‚½
void Enemy::onCollision(GameObject* pTarget)
{
	KillMe();
	pTarget->KillMe();
}