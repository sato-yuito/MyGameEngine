#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
using namespace DirectX;
class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;//
public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();
};

