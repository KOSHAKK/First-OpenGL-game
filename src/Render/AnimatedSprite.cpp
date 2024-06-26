#include "AnimatedSprite.hpp"
#include "Texture2D.hpp"

#include <iostream>

namespace Render {

    AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture2D> pTexture,
        std::string initialSubTexture,
        std::shared_ptr<ShaderProgram> pShaderProgram,
        const glm::vec2& position,
        const glm::vec2& size,
        const float rotation,
        bool lopped)
        : Sprite(pTexture, pShaderProgram, initialSubTexture, position, size, rotation),
          m_lopped(lopped)
    {

        m_pCurrentAnimationDurations = m_statesMap.end();
    }

    void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
    {
        m_statesMap.emplace(std::move(state), std::move(subTexturesDuration));
    }

    void AnimatedSprite::setState(const std::string& newState)
    {
        if (!destruct)
        {
            auto it = m_statesMap.find(newState);
            if (it == m_statesMap.end())
            {
                std::cout << "Can't find animation state: " << newState << std::endl;
                return;
            }

            if (it != m_pCurrentAnimationDurations)
            {
                m_currentAnimationTime = 0;
                m_currentFrame = 0;
                m_pCurrentAnimationDurations = it;
                m_dirty = true;
            }
        }
    }

    void AnimatedSprite::update(const uint64_t delta)
    {



        if (!destruct)
        {
            if (m_pCurrentAnimationDurations != m_statesMap.end())
            {
                m_currentAnimationTime += delta;
                while (m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second)
                {
                    m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;
                    if (!m_lopped && ++m_update_count+1 > m_pCurrentAnimationDurations->second.size())
                    {
                        destroy();
                        break;
                    }

                    ++m_currentFrame;
                    m_dirty = true;
                    if (m_currentFrame == m_pCurrentAnimationDurations->second.size())
                    {
                        m_currentFrame = 0;
                    }
                }
            }
        }
        
    }

    void AnimatedSprite::destroy()
    {
        if (!destruct)
        {
            destruct = true;
            m_statesMap.clear();
        }
    }

    void AnimatedSprite::render(const bool is_mirror) const
    {
        if (!destruct)
        {
            if (m_dirty)
            {
                auto subTexture = m_pTexture->get_subTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);


                const GLfloat textureCoords[] = {
                    // U  V
                    subTexture.left_bottom.x, subTexture.left_bottom.y,
                    subTexture.left_bottom.x, subTexture.right_top.y,
                    subTexture.right_top.x,   subTexture.right_top.y,

                    subTexture.right_top.x,   subTexture.right_top.y,
                    subTexture.right_top.x,   subTexture.left_bottom.y,
                    subTexture.left_bottom.x, subTexture.left_bottom.y
                };

                glBindBuffer(GL_ARRAY_BUFFER, m_VBO_tex_coords);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                m_dirty = false;
            }
            Sprite::render(is_mirror);
        }
    }
}