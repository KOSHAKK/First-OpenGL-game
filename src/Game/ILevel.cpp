#include <algorithm>
#include <iostream>
#include <cmath>

#include <glm/vec2.hpp>

#include "ILevel.hpp"
#include "MyceliumBlock.hpp"
#include "../Resources/ResourceManager.hpp"


void ILevel::render()
{
	for (auto& obj : m_game_objects) {
		if (obj)
		{
			obj->render();
		}
	}
}

void ILevel::update(const uint64_t delta)
{
	for (auto& obj : m_game_objects) 
		if (obj) obj->update(delta);
}

unsigned int ILevel::get_width() const
{
	return m_width;
}

unsigned int ILevel::get_height() const
{
	return m_height;
}

ILevel::ILevel(const unsigned int BLOCK_SIZE, const unsigned int width, const unsigned int height)
	: BLOCK_SIZE(BLOCK_SIZE),
	  m_width(width),
	  m_height(height)
{	
}

std::vector<std::shared_ptr<IGameObject>> ILevel::get_object_in_area(const glm::vec2& bottom_left, const glm::vec2& top_right) const
{
	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve(9);

	

	glm::vec2 bottom_left_converted(std::clamp(bottom_left.x - BLOCK_SIZE, 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - BLOCK_SIZE - bottom_left.y - BLOCK_SIZE, 0.f, static_cast<float>(get_height())));

	


	glm::vec2 top_right_coverted(std::clamp(top_right.x - BLOCK_SIZE, 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - BLOCK_SIZE - top_right.y - BLOCK_SIZE, 0.f, static_cast<float>(get_height())));


	size_t startX = static_cast<size_t>(floor(bottom_left_converted.x / BLOCK_SIZE));
	size_t EndX = static_cast<size_t>(ceil(top_right_coverted.x / BLOCK_SIZE));

	size_t startY = static_cast<size_t>(floor(top_right_coverted.y / BLOCK_SIZE));
	size_t EndY = static_cast<size_t>(ceil(bottom_left_converted.y / BLOCK_SIZE));
	




	for (size_t current_column = startX; current_column <= EndX; current_column++)
	{
		for (size_t current_row = startY; current_row <= EndY; current_row++)
		{
			auto& currentObject = m_game_objects[current_row * (get_width() / BLOCK_SIZE) + current_column];
			if (currentObject)
			{
				output.push_back(currentObject);
			}
		}
	}

	//std::cout << output.size() << std::endl;	

	return output;
}

bool ILevel::has_object_down(const glm::vec2& bottom_left, const glm::vec2& top_right) const
{
	glm::vec2 bottom_left_converted(std::clamp(bottom_left.x - BLOCK_SIZE, 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - BLOCK_SIZE - bottom_left.y - BLOCK_SIZE, 0.f, static_cast<float>(get_height())));


	glm::vec2 top_right_coverted(std::clamp(top_right.x - BLOCK_SIZE, 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - BLOCK_SIZE - top_right.y - BLOCK_SIZE, 0.f, static_cast<float>(get_height())));

	top_right_coverted.y -= top_right.y - bottom_left.y;




	int startX = (bottom_left_converted.x / BLOCK_SIZE) + 1;
	int EndX = (top_right_coverted.x / BLOCK_SIZE) + 1;

	int y = ((bottom_left_converted.y - 20) / (BLOCK_SIZE)) + 2;


	for (size_t x = startX; x <= EndX; x++)
	{
		auto obj = m_game_objects[y * (get_width() / BLOCK_SIZE) + x];
		if (obj && obj->type() != IGameObject::EObjectType::FRUIT)
		{
			return true;
		}
	}

	return false;
}

bool ILevel::has_object_up(const glm::vec2& bottom_left, const glm::vec2& top_right) const
{
	glm::vec2 bottom_left_converted(std::clamp(bottom_left.x - BLOCK_SIZE, 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - BLOCK_SIZE - bottom_left.y - BLOCK_SIZE, 0.f, static_cast<float>(get_height())));


	glm::vec2 top_right_coverted(std::clamp(top_right.x - BLOCK_SIZE, 0.f, static_cast<float>(get_width())),
		std::clamp(get_height() - BLOCK_SIZE - top_right.y - BLOCK_SIZE, 0.f, static_cast<float>(get_height())));

	top_right_coverted.y -= top_right.y - bottom_left.y;




	int startX = (bottom_left_converted.x / BLOCK_SIZE) + 1;
	int EndX = (top_right_coverted.x / BLOCK_SIZE) + 1;

	int y = ((bottom_left_converted.y - 20) / (BLOCK_SIZE));


	for (size_t x = startX; x <= EndX; x++)
	{
		auto obj = m_game_objects[y * (get_width() / BLOCK_SIZE) + x];
		if (obj && obj->type() != IGameObject::EObjectType::FRUIT)
		{
			return true;
		}
	}

	return false;
}

unsigned int ILevel::get_block_size() const
{
	return BLOCK_SIZE;
}


