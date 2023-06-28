#include"Dice.h"

void Dice::InitVertexData()
{
	// ���_���
	vertices_ =
	{
		//�O��
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // �l�p�`�̒��_�i����j0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // �l�p�`�̒��_�i�E��j1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // �l�p�`�̒��_�i�E���j2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // �l�p�`�̒��_�i����) 3
		//���
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,1.0f, 0.0f)},
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,1.0f, 0.0f) },
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,1.0f, 0.0f) },
		//����
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f)},
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f) },
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f) },
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f, 0.0f)},
		//�E��
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f,0.0f, 0.0f) },
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,0.0f,0.0f, 0.0f) },
		//���
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,1.0f,0.0f, 0.0f) },
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,1.0f,0.0f, 0.0f) },
		//����
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)},
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)},

	};
	vertexNum_ = vertices_.size();
}

void Dice::InitIndexData()
{
	//�C���f�b�N�X���
	index_ = { 0,2,3, 0,1,2,
		            4,7,6, 4,6,5,
		            8,11,10, 8,10,9,
		            12,14,15, 12,13,14,
		            16,18,19, 16,17,18
		            ,20,23,22, 20,22,21};
	indexNum_ = index_.size();
}