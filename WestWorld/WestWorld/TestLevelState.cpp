#include "TestLevelState.h"

TestLevelState TestLevelState::m_TestLevelState;

TestLevelState::TestLevelState(){
}


TestLevelState::~TestLevelState(){
}

TestLevelState* TestLevelState::Instance(){
	return(&m_TestLevelState);
}

void TestLevelState::Init(CGameManager* pManager) {

}
void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {

}
void TestLevelState::KeyboardEvent(CGameManager* pManager) {

}