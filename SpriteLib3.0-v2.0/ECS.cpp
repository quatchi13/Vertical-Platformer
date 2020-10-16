#include "ECS.h"

entt::registry* ECS::m_reg = nullptr;

void ECS::AttachRegister(entt::registry * reg)
{
	//Attach reference to the registry
	m_reg = reg;
}

void ECS::UnattachRegister()
{
	//Unattaches the register
	m_reg = nullptr;
}

unsigned ECS::CreateEntity()
{
	//create the entity
	auto entity = m_reg->create();

	//Attach Entity Identifier to the entity
	//m_reg->assign<EntityIdentifier>(entity);

	//Return entity ID
	return entity;
}

void ECS::DestroyEntity(unsigned entity)
{
	//Destroys the entity
	m_reg->destroy(entity);
}

void ECS::SetIsMainCamera(unsigned entity, bool mainCamera)
{
	if (mainCamera)
	{
		MainEntities::MainCamera(entity);
	}
}

void ECS::SetIsMainPlayer(unsigned entity, bool mainPlayer)
{
	if (mainPlayer)
	{
		MainEntities::MainPlayer(entity);
	}
}

void ECS::SetIsGraphOne(unsigned entity, bool graphOne)
{
	if (graphOne)
	{
		MainEntities::GraphOne(entity);
	}
}

void ECS::SetIsGraphTwo(unsigned entity, bool graphTwo)
{
	if (graphTwo)
	{
		MainEntities::GraphTwo(entity);
	}
}

void ECS::SetIsWin(unsigned entity, bool win)
{
	if (win)
	{
		MainEntities::Win(entity);
	}
}