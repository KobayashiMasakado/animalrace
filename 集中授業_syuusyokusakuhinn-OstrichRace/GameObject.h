#include "pch.h"

class GameObject
{
private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;
	//速度
	DirectX::SimpleMath::Vector3 m_vector;
public:
	//位置 全て
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_position;
	}
	void SetPos(DirectX::SimpleMath::Vector3 pos)
	{
		this->m_position = pos;
	}
	////位置 x
	//float GetPosX()
	//{
	//	return m_position.x;
	//}
	//void SetPosX(float posx)
	//{
	//	this->m_position.x = posx;
	//}
	////位置 y
	//float GetPosY()
	//{
	//	return m_position.y;
	//}
	//void SetPosY(float posy)
	//{
	//	this->m_position.y = posy;
	//}
	////位置 z
	//float GetPosZ()
	//{
	//	return m_position.z;
	//}
	//void SetPosZ(float posz)
	//{
	//	this->m_position.z = posz;
	//}

	//速度
	DirectX::SimpleMath::Vector3 GetVec()
	{
		return m_vector;
	}
	void SetVec(DirectX::SimpleMath::Vector3 vec)
	{
		this->m_vector = vec;
	}
};