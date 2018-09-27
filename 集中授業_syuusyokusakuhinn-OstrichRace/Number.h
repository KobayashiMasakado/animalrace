#pragma once
#include "pch.h"
class Number
{
private:
	int m_num;
	DirectX::SimpleMath::Vector2 m_pos;
	ID3D11ShaderResourceView* m_texture[10];
public:
	Number();
	~Number();
	void Draw(DirectX::SpriteBatch* spriteBatch);

	void SetNum(int num);
	void SetPos(DirectX::SimpleMath::Vector2 pos);

	void SetTexture(int n,ID3D11ShaderResourceView* texture);
};