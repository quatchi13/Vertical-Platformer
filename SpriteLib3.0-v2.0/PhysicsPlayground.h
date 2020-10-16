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
	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void makePlatform(int, int, int);

protected:

};
