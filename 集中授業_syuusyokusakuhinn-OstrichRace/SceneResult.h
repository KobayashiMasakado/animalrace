#pragma once

#include "SceneBase.h"

class SceneResult : public SceneBase
{
private:

public:
	SceneResult();
	~SceneResult();

	//������
	void Initialize() override {}
	//�X�V
	void Update(DX::StepTimer timer) override {}
	//�`��
	void Render() override {}
	//�I������
	void Finalize() override {}
};