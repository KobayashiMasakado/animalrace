#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"

class Goal : public CollisionCapsule
{
private:

public:
	//コンストラクタ
	Goal();
	//デストラクタ
	~Goal();
	//更新
	bool Update(float elapsedTIme);
	//描画
	void Render();
	//エフェクトの設定関数
	void SetUpEffect();

	void CourseCreate();
};