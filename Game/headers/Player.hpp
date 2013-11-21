#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

class Player : public Entity
{
    public:
        void processEvents();
        void update(sf::Time dt);
        void draw();
    private:
};

#endif // PLAYER_HPP_INCLUDED
