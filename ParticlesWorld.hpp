/*
* Project: RayLibParticle
 * File: ParticlesWorld.hpp
 * Author: olegfresi
 * Created: 20/06/26 15:20
 *
 * Copyright © 2026 olegfresi
 *
 * Licensed under the MIT License. You may obtain a copy of the License at:
 *
 *     https://opensource.org/licenses/MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once
#include <random>
#include <vector>
#include "Particle.hpp"


namespace Particles
{
    class ParticlesWorld
    {
    public:
        static constexpr size_t INITIAL_PARTICLES_COUNT = 100;

        ParticlesWorld()
        {
            for(size_t i{0}; i < INITIAL_PARTICLES_COUNT; i++)
            {
                Particle particle{};
                particle.position = Vector2{RandomRange(0, static_cast<float>(GetScreenWidth())),
                                            RandomRange(0, static_cast<float>(GetScreenHeight()))};

                particle.velocity = Vector2{RandomRange(-MAX_INITIAL_VELOCITY, MAX_INITIAL_VELOCITY),
                                            RandomRange(-MAX_INITIAL_VELOCITY, MAX_INITIAL_VELOCITY)};

                particle.radius = RandomRange(4.0f, 7.0f);

                m_particles.push_back(particle);
            }
        }


        [[nodiscard]] const std::vector<Particle>& GetParticles() const { return m_particles; }

        void Draw() const
        {
            for(const auto& particle : m_particles)
                DrawCircle(particle.position.x, particle.position.y, particle.radius, WHITE);
        }

        static float RandomRange(float min, float max)
        {
            static std::mt19937 generator{ std::random_device{}() };
            std::uniform_real_distribution range{ min, max };

            return range(generator);
        }

        void Update(float deltaTime)
        {


            for(auto& particle : m_particles)
            {
                particle.position.x += particle.velocity.x * deltaTime;
                particle.position.y += particle.velocity.y * deltaTime;

                particle.velocity.x *= DRAG;
                particle.velocity.y *= DRAG;

                particle.velocity.y += GRAVITY;

                bool hitLeft  { particle.position.x - particle.radius < 0};
                bool hitRight { particle.position.x + particle.radius > static_cast<float>(GetScreenWidth())};

                bool hitTop    { particle.position.y - particle.radius < 0};
                bool hitBottom { particle.position.y + particle.radius > static_cast<float>(GetScreenHeight())};

                if(hitRight)
                {
                    particle.position.x = static_cast<float>(GetScreenWidth()) - particle.radius;
                    particle.velocity.x *= -BOUNCE;
                }

                if(hitLeft)
                {
                    particle.position.x = particle.radius;
                    particle.velocity.x *= -BOUNCE;
                }

                if(hitTop)
                {
                    particle.position.y = particle.radius;
                    particle.velocity.y *= -BOUNCE;
                }

                if(hitBottom)
                {
                    particle.position.y = static_cast<float>(GetScreenHeight()) - particle.radius;
                    particle.velocity.y *= -BOUNCE;
                }
            }
        }

    private:
        std::vector<Particle> m_particles{};
    };
}