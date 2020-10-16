#include "MainEntities.h"

int MainEntities::m_mainCamera = 0;
int MainEntities::m_mainPlayer = 0;
int MainEntities::m_graphOne = 0;
int MainEntities::m_graphTwo = 0;

int MainEntities::MainCamera()
{
	return m_mainCamera;
}

int MainEntities::MainPlayer()
{
	return m_mainPlayer;
}

int MainEntities::GraphOne()
{
	return m_graphOne;
}

int MainEntities::GraphTwo()
{
	return m_graphTwo;
}

void MainEntities::MainCamera(int main)
{
	m_mainCamera = main;
}

void MainEntities::MainPlayer(int main)
{
	m_mainPlayer = main;
}

void MainEntities::GraphOne(int main)
{
	m_graphOne = main;
}

void MainEntities::GraphTwo(int main)
{
	m_graphTwo = main;
}
