#include "SceneManager.h"
#include"../TestScene.h"
#include "Direct3D.h"
#include"../PlayScene.h"
#include"Model.h"
using namespace Direct3D;
SceneManager::SceneManager(GameObject* parent)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentScneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentScneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//シーンを実際に切り替える
	//今のシーンとnextシーンが別だったら切り替え
	if (currentScneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//ロードしたデータを全部削除
		Model::Release();
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		}
		currentScneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}
