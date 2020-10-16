#ifndef __MAINENTITIES_H__
#define __MAINENTITIES_H__

class MainEntities
{
public:
	//Getters
	static int MainCamera();
	static int MainPlayer();
	static int GraphOne();
	static int GraphTwo();

	//Setters
	static void MainCamera(int main);
	static void MainPlayer(int main);
	static void GraphOne(int main);
	static void GraphTwo(int main);

private:
	static int m_mainCamera;
	static int m_mainPlayer;
	static int m_graphOne;
	static int m_graphTwo;
};

#endif // !__MAINENTITIES_H__
