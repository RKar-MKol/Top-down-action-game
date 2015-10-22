#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define ScreenHeight 640
#define ScreenWidth 800

using namespace std;


class Effect : public sf::Drawable, public sf::Transformable
{
    friend class Graphic_Engine;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
    friend class Graphic_Engine;
    //Pola
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
        sf::Time until_ready;
        bool launched;
    };
    vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Time m_lifebegin;
    sf::Vector2f m_emitter;
    bool ToDelete;
    sf::RenderStates tekstura;

    //Konstruktory
    ParticleSystem() {}
    ParticleSystem(unsigned int count, sf::Vector2f emitter, sf::Color MINcolor,
                   sf::Color MAXcolor, sf::Time lifetime = sf::seconds(3));
    ParticleSystem(ParticleSystem& Part);
    void operator=(const ParticleSystem& Part);


    //Metody
    void SetEmitter(sf::Vector2f emitter) { m_emitter = emitter; }
    void launchParticle(size_t index);
    void update(sf::Time elapsed);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

class Graphic_Engine
{
    sf::RenderWindow GameWindow;
public:
    //Konstruktor i Destruktor
    Graphic_Engine();
    ~Graphic_Engine(); //TRZEBA OCZYSCIC WEKTORY

    sf::RenderWindow* GetWindow() {return &GameWindow;}
    sf::Clock clock;
////////////////////////////////////////////////////////  PARTICLE  ///////////////////////////////////////////
private:
    vector<ParticleSystem*> AllParticleSystems;
    vector<ParticleSystem*> PredefinedParticleSystems; //zmienic z wektora na mape z enumem
public:
    void ParticlesDraw();
    void CreateParticleSystemPredefined(unsigned int number);
    void CreateParticleSystemNew(); //TRZEBA DODAC PARAMETRY
    //Tekstury
    sf::Texture teksturapls;
};

