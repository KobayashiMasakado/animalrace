#pragma once

#include "SceneBase.h"

class SceneResult : public SceneBase
{
private:

public:
	SceneResult();
	~SceneResult();

	//初期化
	void Initialize() override {}
	//更新
	void Update(DX::StepTimer timer) override {}
	//描画
	void Render() override {}
	//終了処理
	void Finalize() override {}
};