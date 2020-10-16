#pragma once

#include "Scene.h"

class PhysicsPlayground : public Scene
{
public:
	PhysicsPlayground(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;
	float timer = 0;
	float timerTwo = 0;
	bool canJump = false;
	bool inAir = false;
	bool isMoveing = false;
	float speed = 0;
	float additionalSpeed = 0;
	bool showGraph1 = true;
	float graph1Transparency;
	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void makePlatform(int, int, int);

	void makeImage(std::string fileName, float length, float width, float x, float y, float z, float transparency);

protected:

};
