#ifndef VECTORUTIL_HPP_INCLUDED

#include <SFML/System.hpp>

class VectorUtil{
public:
    VectorUtil();
    virtual ~VectorUtil();

    float length (sf::Vector2f *v);
    float distance(sf::Vector2f a,sf::Vector2f b);
    sf::Vector2f normalize (sf::Vector2f v);
    sf::Vector2f normalize (sf::Vector2f *v);
    sf::Vector2f truncate(sf::Vector2f *v, float maxNum);
    sf::Vector2f truncate(sf::Vector2f v, float maxNum);
     sf::Vector2f truncateLength (sf::Vector2f v, float maxLength);
};


#endif
