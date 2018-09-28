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
	// ���f����ǂݍ���
	// �G�t�F�N�g�t�@�N�g���[ 
	EffectFactory fx(device);
	// ���f���̃e�N�X�`���̓����Ă���t�H���_���w�肷�� 
	fx.SetDirectory(L"Resources\\Models");      //�e�N�X�`���t����cmo������ꍇ��Ɏ����Ă���
	m_playerModel = Model::CreateFromCMO(device, L"Resources\\Models\\Ostrich&Human.cmo", fx);
	m_cpuModel  = Model::CreateFromCMO(device, L"Resources\\Models\\Tiger.cmo", fx);
}
