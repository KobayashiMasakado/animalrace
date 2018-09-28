#pragma once

#include <Model.h>
#include "Utility.h"

class ModelDate : public SingletonBase<ModelDate>
{
private:
	std::unique_ptr<DirectX::Model> m_playerModel;
	std::unique_ptr<DirectX::Model> m_cpuModel;

public:
	ModelDate();
	~ModelDate();

	void Create(ID3D11Device* device);

	DirectX::Model* GetPlayer() { return m_playerModel.get(); }
	DirectX::Model* GetCPU() { return m_cpuModel.get(); }
};