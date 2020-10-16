#include "PhysicsPlayground.h"
#include "Utilities.h"
#include "Math.h"
#include "Player.h"



PhysicsPlayground::PhysicsPlayground(std::string name)
	: Scene(name)
{
	
	m_gravity = b2Vec2(0.f, -7500.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void PhysicsPlayground::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;
	

	//Setup MainCamera Entity
	{
		/*Scene::CreateCamera(m_sceneReg, vec4(-75.f, 75.f, -75.f, 75.f), -100.f, 100.f, windowWidth, windowHeight, true, true);*/

		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
		

		//Attaches the camera to vert and horiz scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	//Setup SKY background Entity
	
	makeImage("sky.png", 250, 950, 0.f, 290.f, 0.f, 1.f);

	makeImage("CAKE.png", 15, 15, 100.f, 641.f, 1.f, 1.f);


	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsGraphOne(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Speed Graphs 1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(85.f, 75.f, 4.f));
	}
	
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsGraphTwo(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "Speed Graphs 2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(85.f, 75.f, 4.f));
	}


	makeImage("Speed Graphs 1.png", 100, 60, 85.f, 75.f, 4.f, 0.f);



	//Setup static GROUND
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "GROUND.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 2000, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(30.f), float32(-40.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);

	}

	//x, y, length kdjfghsk
	//                       vvvv number of platform "rows" ;~; 
	makePlatform(0, 0, 100);//1st platform bottom center
	makePlatform(-72, 35, 80);//2nd plat left side
	makePlatform(72, 35, 80);//2nd plat right side
	makePlatform(0, 70, 50);//3rd plat center (first plat cut in half)
	makePlatform(-72, 105, 50);//4th plat to the left
	makePlatform(0, 140, 50);//5th plat to the middle 
	makePlatform(72, 175, 50);//6th plat to the right
	makePlatform(-10, 210, 50);//7th plat middle tad left
	makePlatform(-87, 245, 50);//8th plat left to the wall
	makePlatform(-30, 280, 25);//9th plat leftish (second time being cut in half)
	makePlatform(-70, 315, 25);//10th plat left close to wall but not really
	makePlatform(-20, 350, 25);//11th plat leftish
	makePlatform(-10, 385, 25);//12th plat left ish
	makePlatform(0, 420, 25);//13th plat middle also sidenote 420 hell yeah
	makePlatform(10, 455, 25);//14th plat rightish 
	makePlatform(75, 350, 12);//11th plat right ish 
	makePlatform(106, 385, 12);//12th plat right ladder (3rd time cut again)
	makePlatform(106, 420, 12);//13th plat right ladder 
	makePlatform(106, 455, 12);//14th plat right ladder 
	makePlatform(106, 490, 12);//15th plat right ladder 
	makePlatform(106, 525, 12);//16th plat right ladder
	makePlatform(60, 525, 8);//16th rightish (4th time its cut holy hell this will be nightmare)
	makePlatform(20, 525, 8);//16th rightish
	makePlatform(-20, 525, 8);//16th leftish 
	makePlatform(-75, 490, 8);//15th left below row
	makePlatform(-108, 525, 8);//16th left wall 
	makePlatform(-75, 560, 4);//17th middle left ish 
	makePlatform(-50, 595, 4);//18th left middle ish 
	makePlatform(-20, 595, 4);//18th left ish 
	makePlatform(10, 595, 4);//18th right ish 
	makePlatform(40, 595, 4);//18th right more ish
	makePlatform(70, 595, 4);//18th right more more right ish
	makePlatform(100, 630, 24);//19th right to the wall where CAKE :O

	//Setup static BREEK
	{
		int boxNumber = 26;
		int wallHeight = 0;
		for (; boxNumber > 0; boxNumber--)
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<PhysicsBody>(entity);

			//Sets up components
			std::string fileName = "breeks.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

			auto& tempSpr = ECS::GetComponent<Sprite>(entity);
			auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

			float shrinkX = 0.f;
			float shrinkY = 0.f;
			b2Body* tempBody;
			b2BodyDef tempDef;
			tempDef.type = b2_staticBody;
			tempDef.position.Set(float32(-128.f), float32(wallHeight + -20.f));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);
			wallHeight += 32;
		}
		
	}
	//Setup static BREEK
	{
		int boxNumber = 26;
		int wallHeight = 0;
		for (; boxNumber > 0; boxNumber--)
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<PhysicsBody>(entity);

			//Sets up components
			std::string fileName = "breeks.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

			auto& tempSpr = ECS::GetComponent<Sprite>(entity);
			auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

			float shrinkX = 0.f;
			float shrinkY = 0.f;
			b2Body* tempBody;
			b2BodyDef tempDef;
			tempDef.type = b2_staticBody;
			tempDef.position.Set(float32(128.f), float32(wallHeight + -20.f));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);
			wallHeight += 32;
		}

	}

	//Setup static BREEK
	{
		int boxNumber = 10;
		int wallHeight = 0;
		for (; boxNumber > 0; boxNumber--)
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<PhysicsBody>(entity);

			//Sets up components
			std::string fileName = "breeks.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

			auto& tempSpr = ECS::GetComponent<Sprite>(entity);
			auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

			float shrinkX = 0.f;
			float shrinkY = 0.f;
			b2Body* tempBody;
			b2BodyDef tempDef;
			tempDef.type = b2_staticBody;
			tempDef.position.Set(float32(wallHeight + -103.f), float32( 764.f));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);
			wallHeight += 32;
		}

	}
	//Setup static CAKE

	//SLOOM entity
	{
		/*Scene::CreatePhysicsSprite(m_sceneReg, "LinkStandby", 80, 60, 1.f, vec3(0.f, 30.f, 2.f), b2_dynamicBody, 0.f, 0.f, true, true)*/

		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<Player>(entity);

		//Sets up the components
		//set up components
		std::string filename = "spritesheets/Sloom.png";
		std::string animations = "Sloom.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 2.f));
		ECS::GetComponent<Player>(entity).InitPlayer(filename, animations, 16, 16, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity));


		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 4.f;
		float shrinkY = 11.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(0.f), float32(-10.f));
		tempDef.angle = Transform::ToRadians(0.f);

		tempBody = m_physicsWorld->CreateBody(&tempDef);
		std::cout << "sdfgsdfgs" << tempSpr.GetWidth() - shrinkX;
		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);

		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetBody()->SetFixedRotation(true);
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	
}

void PhysicsPlayground::Update()
{
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	Scene::AdjustScrollOffset();
	player.Update();
}


void PhysicsPlayground::KeyboardHold()
{
	auto& phys = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	
	isMoveing = false;
	
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (physMove)
	{
		if (player.GetVelocity().y == 0)
		{
			canJump = true;
			inAir = false;
		}
		if (Input::GetKey(Key::Space) && canJump == true)
		{
			isMoveing = true;
			if (timer < 0.4) {
				timer += Timer::deltaTime;
				vel += b2Vec2(0.f, 70);
			}

		}
		else
		{
			inAir = true;
			canJump = false;
			timer = 0;

		}



		if (Input::GetKey(Key::A))
		{
			isMoveing = true;
			if (inAir)
			{
				vel += b2Vec2(-50.f, -15.f);
			}
			else
			{
				vel += b2Vec2(-50.f, 0.f);
			}

		}
		if (Input::GetKey(Key::LeftArrow))
		{
			isMoveing = true;
			vel += b2Vec2(-50.f, 0.f);
		}

		if (Input::GetKey(Key::D))
		{
			isMoveing = true;
			if (inAir)
			{
				vel += b2Vec2(50.f, -15.f);
			}
			else
			{
				vel += b2Vec2(50.f, 0.f);
			}
		}
		if (Input::GetKey(Key::RightArrow))
		{
			isMoveing = true;
			vel += b2Vec2(50.f, 0.f);
		}



		if (isMoveing)
		{
			additionalSpeed += 1;
			if (additionalSpeed < 5)
			{
				speed = sqrt(additionalSpeed);
			}
			if (additionalSpeed > 15)
			{

				speed = pow(speed, 1.5);
			}
			if (speed > 25)
			{
				speed = 25;
			}
			if (speed < 0)
			{
				speed = 0;
			}

		}
		else
		{
			additionalSpeed = 0;
			speed -= 10;
			if (speed < 0)
			{
				speed = 0;
			}

		}

		timerTwo += Timer::deltaTime;
		auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphOne());
		if (image.GetTransparency() == 1.f)
		{
			std::cout << speed << ", " << timerTwo << "\n";
		}
		player.GetBody()->SetLinearVelocity(speed * vel);
		//spare comment

		
	}
	else
	{
		if (player.GetVelocity().y == 0)
		{
			canJump = true;
			inAir = false;
		}
		if (Input::GetKey(Key::Space) && canJump == true)
		{
			isMoveing = true;
			if (timer < 0.4) {
				timer += Timer::deltaTime;
				counter++;
				player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, player.GetPosition().y + speed * Timer::deltaTime), 0);
				if (player.GetPosition().y >= -4 && player.GetPosition().y <= 4 && player.GetPosition().x >= -50 && player.GetPosition().x <= 50)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, -6.5), 0);
				}
				if (player.GetPosition().y >= 31 && player.GetPosition().y <= 39 && player.GetPosition().x >= -112 && player.GetPosition().x <= -32)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 28.5), 0);
				}
				if (player.GetPosition().y >= 31 && player.GetPosition().y <= 39 && player.GetPosition().x >= 32 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 28.5), 0);
				}
				if (player.GetPosition().y >= 66 && player.GetPosition().y <= 74 && player.GetPosition().x >= -40 && player.GetPosition().x <= 40)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 67.5), 0);
				}
				if (player.GetPosition().y >= 101 && player.GetPosition().y <= 109 && player.GetPosition().x >= -97 && player.GetPosition().x <= -47)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 102.5), 0);
				}
				if (player.GetPosition().y >= 136 && player.GetPosition().y <= 144 && player.GetPosition().x >= -25 && player.GetPosition().x <= 25)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 137.5), 0);
				}
				if (player.GetPosition().y >= 171 && player.GetPosition().y <= 179 && player.GetPosition().x >= 47 && player.GetPosition().x <= 97)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 178.5), 0);
				}
				if (player.GetPosition().y >= 206 && player.GetPosition().y <= 214 && player.GetPosition().x >= -35 && player.GetPosition().x <= 15)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 207.5), 0);
				}
				if (player.GetPosition().y >= 241 && player.GetPosition().y <= 249 && player.GetPosition().x >= -112 && player.GetPosition().x <= -62)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 242.5), 0);
				}
				if (player.GetPosition().y >= 276 && player.GetPosition().y <= 284 && player.GetPosition().x >= -42.5 && player.GetPosition().x <= -17.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 277.5), 0);
				}
				if (player.GetPosition().y >= 311 && player.GetPosition().y <= 319 && player.GetPosition().x >= -82.5 && player.GetPosition().x <= -57.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 312.5), 0);
				}
				if (player.GetPosition().y >= 346 && player.GetPosition().y <= 354 && player.GetPosition().x >= -32.5 && player.GetPosition().x <= -7.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 347.5), 0);
				}
				if (player.GetPosition().y >= 381 && player.GetPosition().y <= 389 && player.GetPosition().x >= -22.5 && player.GetPosition().x <= 2.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 382.5), 0);
				}
				if (player.GetPosition().y >= 416 && player.GetPosition().y <= 424 && player.GetPosition().x >= -12.5 && player.GetPosition().x <= 12.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 417.5), 0);
				}
				if (player.GetPosition().y >= 451 && player.GetPosition().y <= 459 && player.GetPosition().x >= -2.5 && player.GetPosition().x <= 22.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 452.5), 0);
				}
				if (player.GetPosition().y >= 346 && player.GetPosition().y <= 354 && player.GetPosition().x >= 69 && player.GetPosition().x <= 81)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 347.5), 0);
				}
				if (player.GetPosition().y >= 381 && player.GetPosition().y <= 389 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 382.5), 0);
				}
				if (player.GetPosition().y >= 416 && player.GetPosition().y <= 424 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 417.5), 0);
				}
				if (player.GetPosition().y >= 451 && player.GetPosition().y <= 459 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 452.5), 0);
				}
				if (player.GetPosition().y >= 486 && player.GetPosition().y <= 494 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 487.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 522.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= 56 && player.GetPosition().x <= 64)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 522.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= 16 && player.GetPosition().x <= 24)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 522.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= -24 && player.GetPosition().x <= -16)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 522.5), 0);
				}
				if (player.GetPosition().y >= 486 && player.GetPosition().y <= 494 && player.GetPosition().x >= -79 && player.GetPosition().x <= -71)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 487.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= -112 && player.GetPosition().x <= -104)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 522.5), 0);
				}
				if (player.GetPosition().y >= 556 && player.GetPosition().y <= 564 && player.GetPosition().x >= -77 && player.GetPosition().x <= -73)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 557.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= -52 && player.GetPosition().x <= -48)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 592.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= 8 && player.GetPosition().x <= 12)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 592.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= 38 && player.GetPosition().x <= 42)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 592.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= 68 && player.GetPosition().x <= 72)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 592.5), 0);
				}
				if (player.GetPosition().y >= 626 && player.GetPosition().y <= 634 && player.GetPosition().x >= 76 && player.GetPosition().x <= 124)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 627.5), 0);
				}
				
			}
	
		}
		else
		{
			if (counter > 0)
			{
				
				player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, player.GetPosition().y - 1.25), 0);
				counter--;
				if (player.GetPosition().y < -20)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, -20), 0);
					counter = 0;
				}
				if (player.GetPosition().y >= -4 && player.GetPosition().y <= 4 && player.GetPosition().x >= -50 && player.GetPosition().x <= 50)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 6.5), 0);
				}
				if (player.GetPosition().y >= 31 && player.GetPosition().y <= 39 && player.GetPosition().x >= -112 && player.GetPosition().x <= -32)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 41.5), 0);
				}
				if (player.GetPosition().y >= 31 && player.GetPosition().y <= 39 && player.GetPosition().x >= 32 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 41.5), 0);
				}
				if (player.GetPosition().y >= 66 && player.GetPosition().y <= 74 && player.GetPosition().x >= -40 && player.GetPosition().x <= 40)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 76.5), 0);
				}
				if (player.GetPosition().y >= 101 && player.GetPosition().y <= 109 && player.GetPosition().x >= -97 && player.GetPosition().x <= -47)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 111.5), 0);
				}
				if (player.GetPosition().y >= 136 && player.GetPosition().y <= 144 && player.GetPosition().x >= -25 && player.GetPosition().x <= 25)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 146.5), 0);
				}
				if (player.GetPosition().y >= 171 && player.GetPosition().y <= 179 && player.GetPosition().x >= 47 && player.GetPosition().x <= 97)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 181.5), 0);
				}
				if (player.GetPosition().y >= 206 && player.GetPosition().y <= 214 && player.GetPosition().x >= -35 && player.GetPosition().x <= 15)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 216.5), 0);
				}
				if (player.GetPosition().y >= 241 && player.GetPosition().y <= 249 && player.GetPosition().x >= -112 && player.GetPosition().x <= -62)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 251.5), 0);
				}
				if (player.GetPosition().y >= 276 && player.GetPosition().y <= 284 && player.GetPosition().x >= -42.5 && player.GetPosition().x <= -17.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 286.5), 0);
				}
				if (player.GetPosition().y >= 311 && player.GetPosition().y <= 319 && player.GetPosition().x >= -82.5 && player.GetPosition().x <= -57.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 321.5), 0);
				}
				if (player.GetPosition().y >= 346 && player.GetPosition().y <= 354 && player.GetPosition().x >= -32.5 && player.GetPosition().x <= -7.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 356.5), 0);
				}
				if (player.GetPosition().y >= 381 && player.GetPosition().y <= 389 && player.GetPosition().x >= -22.5 && player.GetPosition().x <= 2.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 391.5), 0);
				}
				if (player.GetPosition().y >= 416 && player.GetPosition().y <= 424 && player.GetPosition().x >= -12.5 && player.GetPosition().x <= 12.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 426.5), 0);
				}
				if (player.GetPosition().y >= 451 && player.GetPosition().y <= 459 && player.GetPosition().x >= -2.5 && player.GetPosition().x <= 22.5)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 461.5), 0);
				}
				if (player.GetPosition().y >= 346 && player.GetPosition().y <= 354 && player.GetPosition().x >= 69 && player.GetPosition().x <= 81)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 356.5), 0);
				}
				if (player.GetPosition().y >= 381 && player.GetPosition().y <= 389 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 391.5), 0);
				}
				if (player.GetPosition().y >= 416 && player.GetPosition().y <= 424 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 426.5), 0);
				}
				if (player.GetPosition().y >= 451 && player.GetPosition().y <= 459 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 461.5), 0);
				}
				if (player.GetPosition().y >= 486 && player.GetPosition().y <= 494 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 496.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= 100 && player.GetPosition().x <= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 531.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= 56 && player.GetPosition().x <= 64)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 531.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= 16 && player.GetPosition().x <= 24)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 531.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= -24 && player.GetPosition().x <= -16)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 531.5), 0);
				}
				if (player.GetPosition().y >= 486 && player.GetPosition().y <= 494 && player.GetPosition().x >= -79 && player.GetPosition().x <= -71)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 496.5), 0);
				}
				if (player.GetPosition().y >= 521 && player.GetPosition().y <= 529 && player.GetPosition().x >= -112 && player.GetPosition().x <= -104)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 531.5), 0);
				}
				if (player.GetPosition().y >= 556 && player.GetPosition().y <= 564 && player.GetPosition().x >= -77 && player.GetPosition().x <= -73)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 566.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= -52 && player.GetPosition().x <= -48)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 601.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= 8 && player.GetPosition().x <= 12)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 601.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= 38 && player.GetPosition().x <= 42)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 601.5), 0);
				}
				if (player.GetPosition().y >= 591 && player.GetPosition().y <= 599 && player.GetPosition().x >= 68 && player.GetPosition().x <= 72)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 601.5), 0);
				}
				if (player.GetPosition().y >= 626 && player.GetPosition().y <= 634 && player.GetPosition().x >= 76 && player.GetPosition().x <= 124)
				{
					player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x, 636.5), 0);
				}
			}
			
			inAir = true;
			canJump = false;
			timer = 0;
	
		}
	
	
	
		if (Input::GetKey(Key::A))
		{
			isMoveing = true;
			if (inAir)
			{
				player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x - speed * Timer::deltaTime, player.GetPosition().y), 0);
				if (player.GetPosition().x <= -106)
				{
					player.GetBody()->SetTransform(b2Vec2(-104, player.GetPosition().y), 0);
				}

			}
			else
			{
				player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x - speed * Timer::deltaTime, player.GetPosition().y), 0);
				if (player.GetPosition().x <= -106)
				{
					player.GetBody()->SetTransform(b2Vec2(-104, player.GetPosition().y), 0);
				}
			}
	
		}
		if (Input::GetKey(Key::LeftArrow))
		{
			isMoveing = true;
			vel += b2Vec2(-50.f, 0.f);
		}
	
		if (Input::GetKey(Key::D))
		{
			isMoveing = true;
			if (inAir)
			{
				player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x + speed * Timer::deltaTime, player.GetPosition().y), 0);
				if (player.GetPosition().x >= 106)
				{
					player.GetBody()->SetTransform(b2Vec2(104, player.GetPosition().y), 0);
				}
			}
			else
			{
				player.GetBody()->SetTransform(b2Vec2(player.GetPosition().x + speed * Timer::deltaTime, player.GetPosition().y), 0);
				if (player.GetPosition().x >= 112)
				{
					player.GetBody()->SetTransform(b2Vec2(104, player.GetPosition().y), 0);
				}
			}
		}
		if (Input::GetKey(Key::RightArrow))
		{
			isMoveing = true;
			vel += b2Vec2(50.f, 0.f);
		}
	
	
	
		if (isMoveing)
		{
			speed+= 10;
			if (speed > 100)
			{
				speed = 100;
			}
			if (speed < 0)
			{
				speed = 0;
			}
	
		}
		else
		{
			speed -= 20;
			if (speed < 0)
			{
				speed = 0;
			}
	
		}
			
		timerTwo += Timer::deltaTime;
		auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphTwo());
		if (image.GetTransparency() == 1.f) 
		{
			std::cout << speed << ", " << timerTwo << "\n";
		}
		
		player.GetBody()->SetLinearVelocity(speed * vel);
		//spare comment
	
	}
	
}

void PhysicsPlayground::KeyboardDown()
{
	if (Input::GetKeyDown(Key::G))
	{
		if (physMove)
		{
			auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphOne());
			image.SetTransparency(1.f);
		}
		if (physMove == false)
		{
			auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphTwo());
			image.SetTransparency(1.f);
		}
	}

	if (Input::GetKeyDown(Key::H))
	{
		if (physMove)
		{
			auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphOne());
			image.SetTransparency(0.f);
		}
		if (physMove == false)
		{
			auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphTwo());
			image.SetTransparency(0.f);
		}
	}

	if (Input::GetKeyDown(Key::I))
	{
		physMove = true;
	}

	if (Input::GetKeyDown(Key::O))
	{
		physMove = false;
	}
	/*auto& image = ECS::GetComponent<Sprite>(MainEntities::GraphTwo());
	if (Input::GetKeyDown(Key::G))
	{
		image.SetTransparency(1.f);
	}

	if (Input::GetKeyDown(Key::H))
	{
		image.SetTransparency(0.f);
	}*/
}

void PhysicsPlayground::KeyboardUp()
{
}

void PhysicsPlayground::makePlatform(int x, int y, int length)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up components
	std::string fileName = "GROUND.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, length, 8);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(float32(x + 0.f), float32(y + 0.f));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);

}

void PhysicsPlayground::makeImage(std::string fileName, float length, float width, float x, float y, float z, float transparency)
{
	/*Scene::CreateSprite(m_sceneReg, "CAKE.png", 100, 60, 0.5f, vec3(0.f, 0.f, 0.f));*/

		//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);

	//Set up the components
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, length, width);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(x, y, z));
}