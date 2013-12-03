
#include "../headers/VectorUtil.hpp"

VectorUtil::VectorUtil(){
}

VectorUtil::~VectorUtil(){
}

float VectorUtil::length (sf::Vector2f *v){
	return sqrt((v->x * v->x) +(v->y * v->y));
}

sf::Vector2f VectorUtil::normalize (sf::Vector2f v){
	float len = length(&v);
	v.x = v.x / len;
	v.y = v.y / len;
	return v;
}

sf::Vector2f VectorUtil::normalize (sf::Vector2f *v){
	float len = length(v);
	v->x = v->x / len;
	v->y = v->y / len;
	return *v;
}



sf::Vector2f VectorUtil::truncate(sf::Vector2f *v, float maxNum){
    float i = maxNum / length(v);
    i = i < 1.0 ? i : 1.0;
    v->x = v->x * i;
    v->y = v->y * i;
    return *v;
}

