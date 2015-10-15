#include "Graphic_Engine.h"
////////////////////////////
//  PARTICLE SYSTEM
////////////////////////////
ParticleSystem::ParticleSystem(unsigned int count, sf::Vector2f emitter, sf::Color MINcolor,
                   sf::Color MAXcolor, sf::Time lifetime) :
                        m_particles(count), m_lifetime(lifetime), m_emitter(emitter), ToDelete(false)
                        {
                            short red = MAXcolor.r - MINcolor.r + 1;
                            short green = MAXcolor.g - MINcolor.g + 1;
                            short blue = MAXcolor.b - MINcolor.b + 1;
                            short alpha = MAXcolor.a - MINcolor.a + 1;
                            m_vertices = sf::VertexArray(sf::Points, count);
                            for(int i=0;i<count;i++)
                            {
                                m_vertices[i].color = sf::Color(MINcolor.r + rand()%red,
                                                                         MINcolor.g + rand()%green,
                                                                         MINcolor.b + rand()%blue,
                                                                         MINcolor.a + rand()%alpha
                                                                    );
                                m_particles[i].until_ready = sf::seconds(rand()%(int(m_lifetime.asSeconds()/2.0f)));
                                m_particles[i].lifetime = m_lifetime - m_particles[i].until_ready; - sf::seconds(float(rand()%int(ceil(m_lifetime.asSeconds()/4))));
                                m_particles[i].launched = false;
                            }
                        }





ParticleSystem(ParticleSystem& Part)
{
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices = Part.m_vertices;
    sf::Time m_lifetime = Part.m_lifetime;
    sf::Vector2f m_emitter;
    bool ToDelete;
}
void ParticleSystem::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
        if(m_particles[i].until_ready <= sf::Time::Zero )
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
}
void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    target.draw(m_vertices, states);
}
void ParticleSystem::launchParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter;
    }


////////////////////////////
//  GRAPHIC ENGINE
////////////////////////////
Graphic_Engine::Graphic_Engine()
{
    //GAME WINDOW
    GameWindow.create( sf::VideoMode(ScreenWidth,ScreenHeight),"Game" ,sf::Style::Default);

    //WCZYTANIE TEKSTUR


    //STWORZENIE PREDEFINIOWANYCH PARTICLE SYSTEMÓW
    PredefinedParticleSystems.push_back(new ParticleSystem(1000, sf::Vector2f(0,0), sf::Color(200,0,0),
                                                sf::Color(255,0,0), sf::seconds(2)));
}
Graphic_Engine::~Graphic_Engine()
{
    while(!AllParticleSystems.empty()) {delete AllParticleSystems.back(); AllParticleSystems.pop_back();}
    while(!PredefinedParticleSystems.empty()) {delete PredefinedParticleSystems.back(); PredefinedParticleSystems.pop_back();}

}
ParticleSystem* Graphic_Engine::CreateParticleSystemPredefined(unsigned int number)
{
    if(number >= PredefinedParticleSystems.size())
        {cout<<"ZA DUZY NUMER"; return ParticleSystem();}
    else
    {
        ParticleSystem Part(PredefinedParticleSystems[number]);
        AllParticleSystems.push_back(&Part);
        return &Part;
    }
}
void Graphic_Engine::ParticlesDraw()
{
    for(int i =0; i<AllParticleSystems.size();i++)
    {
        if(AllParticleSystems[i]->m_lifetime<=sf::Time::Zero)
            AllParticleSystems[i]->ToDelete = true;
        else
        {
            AllParticleSystems[i]->update(clock.getElapsedTime() - ParticleSystemTimes[i]);
            GameWindow.draw(*AllParticleSystems[i]);

        }
    }
}















