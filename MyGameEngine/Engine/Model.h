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
		//�g�����X�t�H�[��
		Transform transform;
		//�t�@�C����
		std::string filename;
	};
};

