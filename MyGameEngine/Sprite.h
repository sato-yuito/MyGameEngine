#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include<vector>
using namespace DirectX;

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Sprite
{
	
protected:
	UINT64 vertexNum_;
	std::vector<VERTEX> vertices_;
	ID3D11Buffer* pVertexBuffer_;

	UINT64 indexNum;
	std::vector<VERTEX> index_;

	ID3D11Buffer* pIndexBuffer_;//
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;

public:
	Sprite();
	~Sprite();
	HRESULT Initialize();

	void Draw(XMMATRIX& worldMatrix);

	void Release();

private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	void PassDataToCV(DirectX::XMMATRIX& worldMatrix);
	void SetBufferToPipeline();
};