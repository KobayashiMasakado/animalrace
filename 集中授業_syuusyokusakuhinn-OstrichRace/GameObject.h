#include "pch.h"

class GameObject
{
private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;
	//���x
	DirectX::SimpleMath::Vector3 m_vector;
public:
	//�ʒu �S��
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_position;
	}
	void SetPos(DirectX::SimpleMath::Vector3 pos)
	{
		this->m_position = pos;
	}
	////�ʒu x
	//float GetPosX()
	//{
	//	return m_position.x;
	//}
	//void SetPosX(float posx)
	//{
	//	this->m_position.x = posx;
	//}
	////�ʒu y
	//float GetPosY()
	//{
	//	return m_position.y;
	//}
	//void SetPosY(float posy)
	//{
	//	this->m_position.y = posy;
	//}
	////�ʒu z
	//float GetPosZ()
	//{
	//	return m_position.z;
	//}
	//void SetPosZ(float posz)
	//{
	//	this->m_position.z = posz;
	//}

	//���x
	DirectX::SimpleMath::Vector3 GetVec()
	{
		return m_vector;
	}
	void SetVec(DirectX::SimpleMath::Vector3 vec)
	{
		this->m_vector = vec;
	}
};