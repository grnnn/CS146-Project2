#ifndef VECTORUTIL_HPP_INCLUDED

#include <SFML/System.hpp>

class VectorUtil{
public:
    float length (sf::Vector2f v);
    sf::Vector2f normalize (sf::Vector2f v);
    sf::Vector2f truncate(sf::Vector2f v, float maxNum);
};


#endif
