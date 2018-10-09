#pragma once

#include "SceneBase.h"

class SceneResult : public SceneBase
{
private:

public:
	SceneResult();
	~SceneResult();

	//‰Šú‰»
	void Initialize() override {}
	//XV
	void Update(DX::StepTimer timer) override {}
	//•`‰æ
	void Render() override {}
	//I—¹ˆ—
	void Finalize() override {}
};