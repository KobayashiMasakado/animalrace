#include "pch.h"
#include "Number.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Number::Number()
{
	m_num = 0;
}

Number::~Number()
{
}

void Number::Draw(DirectX::SpriteBatch * spriteBatch)
{
	int num = m_num;

	if (num >= 99)
	{
		num = 99;
	}

	int a = num / 10;
	int b = num % 10;

	//int c = num / 10;
	//int d = num % 10;

	//int e = num / 10;
	//int f = num % 10;

	if (a >= 0)
	{
		spriteBatch->Draw(m_texture[a], m_pos);
	}
//	if (b >= 60)
//	{
		spriteBatch->Draw(m_texture[b], Vector2(m_pos.x + 38, m_pos.y));
//	}

//	spriteBatch->Draw(m_texture[c], Vector2(m_pos.x + 50, m_pos.y));
}

void Number::SetNum(int num)
{
	m_num = num;
}

void Number::SetPos(DirectX::SimpleMath::Vector2 pos)
{
	m_pos = pos;
}

void Number::SetTexture(int n, ID3D11ShaderResourceView* texture)
{
	m_texture[n] = texture;
}
