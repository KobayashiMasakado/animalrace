#pragma once

#include <Model.h>
#include "Utility.h"

#include "CollisionMesh.h"

class ModelDate : public SingletonBase<ModelDate>
{
private:
	std::unique_ptr<DirectX::Model> m_playerModel;
	std::unique_ptr<DirectX::Model> m_cpuModel;
	std::unique_ptr<DirectX::Model> m_itemPlayerModel;
	std::unique_ptr<DirectX::Model> m_itemCPUModel;

	std::unique_ptr<DirectX::Model> m_itemPlayerEraseModel;
	std::unique_ptr<DirectX::Model> m_itemCPUEraseModel;

	std::unique_ptr<DirectX::Model> m_itemFunModel;
	std::unique_ptr<DirectX::Model> m_itemFunEraseModel;

	std::unique_ptr<DirectX::Model> m_boxModel;

	std::unique_ptr<DirectX::Model> m_goalModel;
public:
	ModelDate();
	~ModelDate();

	void Create(ID3D11Device* device);

	DirectX::Model* GetPlayer() { return m_playerModel.get(); }
	DirectX::Model* GetCPU() { return m_cpuModel.get(); }
	DirectX::Model* GetItemPlayer() { return m_itemPlayerModel.get(); }
	DirectX::Model* GetItemCPU() { return m_itemCPUModel.get(); }
	DirectX::Model* GetItemFun() { return m_itemFunModel.get(); }
	DirectX::Model* GetItemErasePlayer() { return m_itemPlayerEraseModel.get(); }
	DirectX::Model* GetItemEraseCPU() { return m_itemCPUEraseModel.get(); }
	DirectX::Model* GetItemEraseFun() { return m_itemFunEraseModel.get(); }

	DirectX::Model* GetGoal() { return m_goalModel.get(); }
	DirectX::Model* GetBox() { return m_boxModel.get(); }
};