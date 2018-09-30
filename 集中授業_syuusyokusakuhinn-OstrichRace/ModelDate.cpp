#include "pch.h"
#include "ModelDate.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ModelDate::ModelDate()
{
}

ModelDate::~ModelDate()
{
	m_playerModel.reset();
	m_cpuModel.reset();
	m_itemPlayerModel.reset();
	m_itemCPUModel.reset();
	m_rootModel.reset();
}

void ModelDate::Create(ID3D11Device* device)
{
	// モデルを読み込み
	// エフェクトファクトリー 
	EffectFactory fx(device);
	// モデルのテクスチャの入っているフォルダを指定する 
	fx.SetDirectory(L"Resources\\Models");      //テクスチャ付きのcmoがある場合上に持ってくる
	m_playerModel     = Model::CreateFromCMO(device, L"Resources\\Models\\Ostrich&Human.cmo", fx);
	m_cpuModel        = Model::CreateFromCMO(device, L"Resources\\Models\\Tiger.cmo", fx);
	m_itemPlayerModel = Model::CreateFromCMO(device, L"Resources\\Models\\Item.cmo", fx);
	m_itemCPUModel    = Model::CreateFromCMO(device, L"Resources\\Models\\esaC.cmo", fx);
	m_rootModel       = Model::CreateFromCMO(device, L"Resources\\Models\\Root.cmo", fx);
	
}
