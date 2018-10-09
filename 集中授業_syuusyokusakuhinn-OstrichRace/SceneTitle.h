#pragma once
//#include "pch.h"
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
private:

public:
	SceneTitle();
	~SceneTitle();

	//‰Šú‰»
	void Initialize() override;
	//XV
	void Update(DX::StepTimer timer) override;
	//•`‰æ
	void Render() override;
	//I—¹ˆ—
	void Finalize() override;
};