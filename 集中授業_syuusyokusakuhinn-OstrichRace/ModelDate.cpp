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
}

void ModelDate::Create(ID3D11Device* device)
{
	// モデルを読み込み
	// エフェクトファクトリー 
	EffectFactory fx(device);
	// モデルのテクスチャの入っているフォルダを指定する 
	fx.SetDirectory(L"Resources\\Models");      //テクスチャ付きのcmoがある場合上に持ってくる
	m_playerModel = Model::CreateFromCMO(device, L"Resources\\Models\\Ostrich&Human.cmo", fx);
	m_cpuModel    = Model::CreateFromCMO(device, L"Resources\\Models\\Tiger.cmo", fx);
}
