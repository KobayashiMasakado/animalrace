#pragma once
//#include "pch.h"
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
private:

public:
	SceneTitle();
	~SceneTitle();

	//������
	void Initialize() override;
	//�X�V
	void Update(DX::StepTimer timer) override;
	//�`��
	void Render() override;
	//�I������
	void Finalize() override;
};