#pragma once
#include"Fbx.h"
#include"Transform.h"
#include"Texture.h"
#include<string>
namespace Model
{
	struct ModelData
	{
		//FBX
		Fbx fbx;
		//トランスフォーム
		Transform transform;
		//ファイル名
		std::string filename;
	};
};

