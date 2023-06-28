#include"Dice.h"

void Dice::InitVertexData()
{
	// 頂点情報
	vertices_ =
	{
		//前面
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 四角形の頂点（左上）0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 四角形の頂点（右上）1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 四角形の頂点（右下）2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 四角形の頂点（左下) 3
		//後面
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,1.0f, 0.0f)},
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,1.0f, 0.0f) },
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,1.0f, 0.0f) },
		//左面
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f)},
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f) },
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f) },
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f)},
		//右面
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f,0.0f, 0.0f) },
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f,0.0f, 0.0f) },
		//上面
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,1.0f,0.0f, 0.0f) },
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,1.0f,0.0f, 0.0f) },
		//下面
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)},

	};
	vertexNum_ = vertices_.size();
}

void Dice::InitIndexData()
{
	//インデックス情報
	index_ = { 0,2,3, 0,1,2,
		            4,7,6, 4,6,5,
		            8,11,10, 8,10,9,
		            12,14,15, 12,13,14,
		            16,18,19, 16,17,18
		            ,20,23,22, 20,22,21};
	indexNum_ = index_.size();
}