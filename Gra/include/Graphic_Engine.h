#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

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
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    bool ToDelete;

    //Konstruktory
    ParticleSystem();
    ParticleSystem(unsigned int count, sf::Vector2f emitter, sf::Color MINcolor,
                   sf::Color MAXcolor, sf::Time lifetime = sf::seconds(3));
    ParticleSystem(ParticleSystem& Part);




    //Inne metody
    void ChangeEmitter(sf::Vector2f emitter) { m_emitter = emitter; }
public:



    void launchParticle(std::size_t index);

    //przyda sie operator= albo konstruktor kopiujacy, bedziemy mieli predefiniowane ParticleSystemy
    // takie jak Particle_Blood itp. i przy wywolaniu krwawienia, tworzymy nowy particlesystem.

    //Metody publiczne
    void setEmitter(sf::Vector2f position)
        {m_emitter = position;}
    void update(sf::Time elapsed);

private:
    //Metody prywatne
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
    vector<sf::Time> ParticleSystemTimes;

    vector<ParticleSystem*> PredefinedParticleSystems;
public:
    void ParticlesDraw();
    ParticleSystem* CreateParticleSystemPredefined(unsigned int number);
    ParticleSystem* CreateParticleSystemNew(); //TRZEBA DODAC PARAMETRY
    //Tekstury
};

