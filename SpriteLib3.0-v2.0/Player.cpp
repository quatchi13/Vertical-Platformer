#include "Player.h"

Player::Player()
{
}

Player::Player(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitPlayer(fileName, animationJSON, width, height, sprite, controller, transform, hasPhys, body);

}
void Player::InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	m_sprite = sprite;
	m_animController = controller;
	m_transform = transform;
	m_hasPhysics = hasPhys;
	if (hasPhys)
	{
		m_physBody = body;
	}

	//Initialise the UV's
	m_animController->InitUVs(fileName);

	//loads the texture and sets dimentions
	m_sprite->LoadSprite(fileName, width, height, true, m_animController);
	m_animController->SetVAO(m_sprite->GetVAO());
	m_animController->SetTextureSize(m_sprite->GetTextureSize());

	//Loads the json file
	nlohmann::json animation = File::LoadJSON(animationJSON);

	//IDLE ANIMS

	//idle left
	m_animController->AddAnimation(animation["IDLE"].get<Animation>());
	//idle right
	m_animController->AddAnimation(animation["IDLE"].get<Animation>());
#ifdef TOPDOWN
	//idle up
	m_animController->AddAnimation(animation["IDLE"].get<Animation>());
	//idle down
	m_animController->AddAnimation(animation["IDLE"].get<Animation>());
#endif 
	//WALK ANIMS

	//walk left
	m_animController->AddAnimation(animation["MOVELEFT"].get<Animation>());
	//walk right
	m_animController->AddAnimation(animation["MOVERIGHT"].get<Animation>());
#ifdef TOPDOWN
	//walk up
	m_animController->AddAnimation(animation["idle"].get<Animation>());
	//walk down
	m_animController->AddAnimation(animation["idle"].get<Animation>());
#endif

	//ATTACK ANIMS

	//attack left
	m_animController->AddAnimation(animation["YUMPLEFT"].get<Animation>());
	//attack right
	m_animController->AddAnimation(animation["YUMPRIGHT"].get<Animation>());
#ifdef TOPDOWN
	//attack up
	m_animController->AddAnimation(animation["idle"].get<Animation>());
	//attack down
	m_animController->AddAnimation(animation["idle"].get<Animation>());
#endif

	//Set default animation
	m_animController->SetActiveAnim(IDLELEFT);

}

void Player::Update()
{
	
	if (!m_locked)
	{
		MovementUpdate();
		//std::cout << m_transform->GetPositionX() - lastPos << ", " << m_transform->GetPositionY() << ", " << timePassed << "\n";
		timePassed += Timer::deltaTime;
		//lastPos = m_transform->GetPositionX();
	}

	AnimationUpdate();
}

void Player::MovementUpdate()
{
	m_moving = false;

	if (m_hasPhysics)
	{

		
		
			float speed = 8.f;


			vec3 vel = vec3(0.f, 0.f, 0.f);



#ifdef TOPDOWN
			if (Input::GetKey(Key::W))
			{
				vel = vel + vec3(0.f, 1.f, 0.f);
				m_facing = UP;
				m_moving = true;
			}
			if (Input::GetKey(Key::S))
			{
				vel = vel + vec3(0.f, -1.f, 0.f);
				m_facing = DOWN;
				m_moving = true;
			}
#endif
			if (Input::GetKey(Key::A))
			{
				vel = vel + vec3(-1.f, 0.f, 0.f);
				m_facing = LEFT;
				m_moving = true;
			}
			if (Input::GetKey(Key::D))
			{
				vel = vel + vec3(1.f, 0.f, 0.f);
				m_facing = RIGHT;
				m_moving = true;
			}

			m_physBody->SetVelocity(vel * speed);

		
	}
	else {
		//regular movement
		float speed = 15.f;
#ifdef TOPDOWN
		if (Input::GetKey(Key::W))
		{
			m_transform->SetPositionY(m_transform->GetPositionY() + (speed * Timer::deltaTime));
			m_facing = UP;
			m_moving = true;
		}
		if (Input::GetKey(Key::S))
		{
			m_transform->SetPositionY(m_transform->GetPositionY() - (speed * Timer::deltaTime));
			m_facing = DOWN;
			m_moving = true;
		}
#endif
		if (Input::GetKey(Key::A))
		{
			m_transform->SetPositionX(m_transform->GetPositionX() - (speed * Timer::deltaTime));
			m_facing = LEFT;
			m_moving = true;
		}
		if (Input::GetKey(Key::D))
		{
			m_transform->SetPositionX(m_transform->GetPositionX() + (speed * Timer::deltaTime));
			m_facing = RIGHT;
			m_moving = true;
		}
	}

	
	if (Input::GetKeyDown(Key::Space))
	{
		m_moving = false;

		
			if (m_hasPhysics)
			{
				m_physBody->SetVelocity(vec3());
			}

			m_attacking = true;
			m_locked = true;
		
			
	}
}

void Player::AnimationUpdate()
{
	int activeAnimation = 0;

	if (m_moving)
	{
		//puts anims in the walk catagory
		activeAnimation = WALK;
	}
	else if (m_attacking)
	{
		//puts anims into attack catagory
		activeAnimation = ATTACK;

		//chack if attack anim is done
		if (m_animController->GetAnimation(m_animController->GetActiveAnim()).GetAnimationDone())
		{
			//set to idel anim
			m_locked = false;
			m_attacking = false;
			//reset attack anim
			m_animController->GetAnimation(m_animController->GetActiveAnim()).Reset();

			activeAnimation = IDLE;
		}
	}
	else
	{
		//puts anims into idle catagory
		activeAnimation = IDLE;

	}

	SetActiveAnimation(activeAnimation + (int)m_facing);

}

void Player::SetPhysicsState(int physics)
{
	m_hasPhysics = physics;
}

int Player::GetPhysicsState()
{

	return m_hasPhysics;
}

void Player::SetActiveAnimation(int anim)
{
	m_animController->SetActiveAnim(anim);
}
