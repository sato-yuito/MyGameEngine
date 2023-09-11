#include "Model.h"

#include "Direct3D.h"
namespace Model
{
	vector<ModelData*>modelList;
}

int Model::Load(string filename)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = filename;
	pData->fbx_ = nullptr;

	for (auto &e : modelList)
	{
		if (e->filename_ == filename)
		{
			pData->fbx_ = e->fbx_;
			break;
		}
			
	}

	
	if (pData->fbx_ == nullptr)
	{
		pData->fbx_ = new Fbx;
		pData->fbx_->Load(filename);
	}
	modelList.push_back(pData);
	return(modelList.size() - 1);
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel)
{
	modelList[hModel]->fbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false;
	for (int i = 0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->fbx_ == modelList[j]->fbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->fbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}

void Model::RayCast(int hModel, RayCastData& rayData)
{
	modelList[hModel]->transform_.Calclation();
	//ワールド行列の逆行列
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[hModel]->transform_.GetWorldMatrix());
	//レイの追加点を求める
	XMVECTOR vpass{ rayData.start.x + rayData.dir.x, 
		            rayData.start.y + rayData.dir.y ,
					rayData.start.z + rayData.dir.z ,
					rayData.start.w + rayData.dir.w };
	
	XMVECTOR vstart = XMLoadFloat4(&rayData.start);
	
	vstart = XMVector3TransformCoord(vstart, wInv);
	
	XMStoreFloat4(&rayData.start, vstart); 

	vpass = XMVector3TransformCoord(vpass, wInv);
	
	vpass = vpass; -vstart;
	
	XMStoreFloat4(&rayData.dir, vpass);
	
	modelList[hModel]->fbx_->RayCast(rayData);
}
