#include "pch.h"
#include "InputHandler.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

InputHandler::InputHandler()
{
	m_bUp = new FrontCommand();
	m_bLeft = new LeftSideCommand();
	m_bRight = new RightSideCommand();
}

InputHandler::~InputHandler()
{
	delete m_bUp;
	delete m_bLeft;
	delete m_bRight;
}

std::list<Command*>& InputHandler::HandleInput()
{
	m_cList.clear();

	// キーボードの状態を取得する
	Keyboard::State kb = Keyboard::Get().GetState();
	if (kb.Up)    m_cList.push_back(m_bUp);        //前進
	if (kb.Left)  m_cList.push_back(m_bLeft);      //左旋回
	if (kb.Right) m_cList.push_back(m_bRight);     //右旋回

	return m_cList;
}
