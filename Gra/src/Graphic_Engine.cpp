#include "Graphic_Engine.h"
////////////////////////////
//  PARTICLE SYSTEM
////////////////////////////
ParticleSystem::ParticleSystem(unsigned int count, sf::Vector2f emitter, sf::Color MINcolor,
                               sf::Color MAXcolor, sf::Time lifetime):
    m_particles(count), m_lifetime(lifetime), m_emitter(emitter), ToDelete(false)
{
    short red = (int)MAXcolor.r ;//- (int)MINcolor.r + 1;
    short green = MAXcolor.g - MINcolor.g + 1;
    short blue = MAXcolor.b - MINcolor.b + 1;
    short alpha = MAXcolor.a - MINcolor.a + 1;
    //m_vertices = sf::VertexArray(sf::Quads, count);
    m_vertices = sf::VertexArray(sf::Points, count);
    for(int i=0; i<count; i++)
    {
        m_vertices[i].color = sf::Color(MINcolor.r + rand()%red,
                                        MINcolor.g + rand()%green,
                                        MINcolor.b + rand()%blue,
                                        MINcolor.a + rand()%alpha
                                       );
        m_particles[i].until_ready = sf::seconds(rand()%(int(m_lifetime.asSeconds()/2.0f)));
    //    m_particles[i].lifetime = m_lifetime - m_particles[i].until_ready;
        - sf::seconds(float(rand()%int(ceil(m_lifetime.asSeconds()/4))));
        m_particles[i].launched = false;
    }
}


ParticleSystem::ParticleSystem(ParticleSystem& Part) //DOKONCZYC
{

    for(int i=0;i<Part.m_particles.size();++i)
        this->m_particles.push_back(Part.m_particles[i]);
    this->m_vertices = Part.m_vertices;
    this->m_lifetime = Part.m_lifetime;
    this->m_lifebegin = Part.m_lifebegin;
    this->m_emitter = Part.m_emitter;
    this->ToDelete = Part.ToDelete;
    this->tekstura = Part.tekstura;
}
void ParticleSystem::operator=(const ParticleSystem& Part)
{
    for(int i=0;i<Part.m_particles.size();++i)
        this->m_particles.push_back(Part.m_particles[i]);
    this->m_vertices = Part.m_vertices;
    this->m_lifetime = Part.m_lifetime;
    this->m_lifebegin = Part.m_lifebegin;
    this->m_emitter = Part.m_emitter;
    this->ToDelete = Part.ToDelete;
    this->tekstura = Part.tekstura;
}
void ParticleSystem::update(sf::Time now)
{
    sf::Time elapsed = now - m_lifebegin;
    if(m_lifetime <= elapsed)
        ToDelete = true;

    for (size_t i = 0; i < m_particles.size(); ++i)
        if(m_particles[i].until_ready <= elapsed )
        {

            if(!m_particles[i].launched)
                launchParticle(i);
            Particle& p = m_particles[i];

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds();
            if(ratio>1) ratio = 1;
           // m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
}
void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    //states.texture = NULL;

    // draw the vertex array
    target.draw(m_vertices, states);
}
void ParticleSystem::launchParticle(std::size_t index)
{
    // give a random velocity and lifetime to the particle
    float angle = (rand() % 360) * 3.14f / 180.f;
    float speed = (rand() % 50) + 50.f;
    m_particles[index].velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
    int lifetmp = rand() % m_lifetime.asMilliseconds();
    m_particles[index].lifetime = sf::milliseconds(lifetmp) + sf::milliseconds((m_lifetime.asMilliseconds() - lifetmp)/2);
    m_particles[index].until_ready = sf::milliseconds(rand()% m_particles[index].lifetime.asMilliseconds());
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
    if(!teksturapls.loadFromFile("Las_Drzewo2.png")) cout<<"BRAK TEKSTURY";

    //STWORZENIE PREDEFINIOWANYCH PARTICLE SYSTEMÓW
    //ENUM PARTICLE SYSTEMOW
    //PredefinedParticleSystems.push_back(new ParticleSystem);
    PredefinedParticleSystems.push_back(new ParticleSystem(10000, sf::Vector2f(100,100), sf::Color(0,0,0),   //KREW
                                        sf::Color(200,255,255), sf::seconds(3)));
    /*AllParticleSystems.push_back(new ParticleSystem(1000, sf::Vector2f(100,100), sf::Color(200,0,0),   //KREW
                                        sf::Color(255,0,0), sf::seconds(10)));*/
}
Graphic_Engine::~Graphic_Engine()
{
    while(!AllParticleSystems.empty())
    {
        delete AllParticleSystems.back();
        AllParticleSystems.pop_back();
    }
    while(!PredefinedParticleSystems.empty())
    {
        delete PredefinedParticleSystems.back();
        PredefinedParticleSystems.pop_back();
    }

}
void Graphic_Engine::CreateParticleSystemPredefined(unsigned int number) //zamiast liczby enum
{
    if(number >= PredefinedParticleSystems.size())
    {
        cout<<"ZA DUZY NUMER";
        ParticleSystem Part;
        Part.m_lifebegin = clock.getElapsedTime();
    }
    else
    {
        ParticleSystem* Part = new ParticleSystem(*PredefinedParticleSystems[0]);
        Part->tekstura.texture = &teksturapls;
        AllParticleSystems.push_back(Part);
        Part->m_lifebegin = clock.getElapsedTime();
    }
}
void Graphic_Engine::ParticlesDraw()
{

    bool RunDelete = false;
    for(int i =0; i<AllParticleSystems.size(); i++)
    {
        //cout<<endl<<AllParticleSystems.size()<<endl;
            if(AllParticleSystems[i]->ToDelete == true) RunDelete = true;
            AllParticleSystems[i]->update(clock.getElapsedTime());
            GameWindow.draw(*AllParticleSystems[i]);
    }
    if(RunDelete)
        for(vector<ParticleSystem*>::iterator it = AllParticleSystems.begin();it!=AllParticleSystems.end();++it )
            if((*it)->ToDelete)
                {
                    vector<ParticleSystem*>::iterator p = it;
                    --it;
                    AllParticleSystems.erase(p);
                }
}















