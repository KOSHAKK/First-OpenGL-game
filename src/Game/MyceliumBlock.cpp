#include "MyceliumBlock.hpp"
#include "IGameObject.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Render/Sprite.hpp"
#include <string>
#include <iostream>

MyceliumBlock::MyceliumBlock(const EType block_type, const glm::vec2& pos, const glm::vec2& scale, const float rotate)
	: m_type(block_type)

{
	m_object_type = IGameObject::EObjectType::MYCELIUM_BLOCK;
	static unsigned int counter = 0;
	counter++;

	switch (m_type)
	{
	case MyceliumBlock::EType::MYCELIUM_BLOCK_1:
		m_sprite = ResourceManager::load_sprite("mycelium_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "mycelium_block_1");
		break;
	case MyceliumBlock::EType::MYCELIUM_BLOCK_2:
		m_sprite = ResourceManager::load_sprite("mycelium_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "mycelium_block_2");
		break;
	case MyceliumBlock::EType::MYCELIUM_BLOCK_3:
		m_sprite = ResourceManager::load_sprite("mycelium_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "mycelium_block_3");
		break;
	case MyceliumBlock::EType::MYCELIUM_DIRT_1:
		m_sprite = ResourceManager::load_sprite("mycelium_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "mycelium_dirt_1");
		break;
	case MyceliumBlock::EType::MYCELIUM_DIRT_2:
		m_sprite = ResourceManager::load_sprite("mycelium_block" + std::to_string(counter), "default_shader", "terrain_atlas", static_cast<const unsigned int>(scale.x), static_cast<const unsigned int>(scale.y), "mycelium_dirt_2");
		break;
	}

	m_sprite->set_position(pos);
	m_sprite->set_rotate(rotate);


	m_colliderds.emplace_back(PhysicsEngine::AABB(glm::vec2(0.f), scale));
	

}

void MyceliumBlock::update(const uint64_t delta)
{
}

void MyceliumBlock::render() const
{
	m_sprite->render();
}

glm::vec2 MyceliumBlock::get_pos() const
{
	return m_sprite->get_position();
}

glm::vec2 MyceliumBlock::get_size() const
{
	return m_sprite->get_scale();
}

float MyceliumBlock::get_rotation() const
{
	return m_sprite->get_rotate();
}

void MyceliumBlock::set_rotation(const float rotation)
{
	m_sprite->set_rotate(rotation);
}

void MyceliumBlock::set_size(const glm::vec2& size)
{
	m_sprite->set_scale(size);
}

void MyceliumBlock::set_pos(const glm::vec2& position)
{
	m_sprite->set_position(position);
}
