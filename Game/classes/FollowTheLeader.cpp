#include "../headers/VectorUtil.hpp"

#include "../headers/SpaceCraft.hpp"
#include "../headers/FollowTheLeader.hpp"
#include "../headers/LeaderEnemy.hpp"
#include "../headers/FollowEnemy.hpp"
#include <SFML/System/Vector2.hpp>


FollowTheLeader::~FollowTheLeader() {}

FollowTheLeader::FollowTheLeader()
{
}

sf::Vector2f FollowTheLeader::doAction(FollowEnemy& enemy, LeaderEnemy& leader, World& world)
{

//Initialize values
    float LEADER_BEHIND_DIST = 70;   //How close they follow
    float SLOWING_RADIUS = 20;       //Arrive distance
    float SEPARATION_RADIUS =80;     //How far they should detect neighbors
    float MAX_SEPARATION = 4000;        //How far they should move away from neighbors

    VectorUtil* util = new VectorUtil();
     //Some Arbitrary value
    float maxSpeed = enemy.getMaxSpeed();
    sf::Vector2f velocity = enemy.getVelocity();
    sf::Vector2f position = enemy.getPosition();
    sf::Vector2f tv = leader.getVelocity();
    sf::Vector2f leaderPosition = leader.getPosition();

//Calculate point behind leader
    tv.x = tv.x * -1;
    tv.y = tv.y * -1;
    tv = util->normalize(tv);
    tv.x *= LEADER_BEHIND_DIST;
    tv.y *= LEADER_BEHIND_DIST;

    sf::Vector2f behind = tv + leaderPosition;


// Calculate the desired velocity to behind point
    sf::Vector2f desired_velocity = position - behind;
    float distance = util->length(&desired_velocity);
    desired_velocity = util->normalize(desired_velocity);


// Check the distance to detect whether the character is inside the slowing area

    if (distance < SLOWING_RADIUS)
    {
        // Inside the slowing area
        desired_velocity = util->normalize(desired_velocity);
                desired_velocity.x *= maxSpeed * (distance / SLOWING_RADIUS);
                desired_velocity.y *= maxSpeed * (distance / SLOWING_RADIUS);

    }
    else
    {
        // Outside the slowing area
        //desired_velocity = util->normalize(desired_velocity);
        desired_velocity.x *= maxSpeed;
                desired_velocity.y *= maxSpeed;

    }

//Desired velocity slowed

    sf::Vector2f steering = desired_velocity - velocity; //Set the steering

    velocity = util->truncate (velocity + steering , maxSpeed);

//Separation

    sf::Vector2f force;
    int neighborCount = 0;

    for(auto currentEnemy = world.getFollowEnemies().begin(); currentEnemy != world.getFollowEnemies().end(); ++currentEnemy){ //doStuff}

        if ((*currentEnemy != &enemy) && (util->distance((**currentEnemy).getPosition(), position) <= SEPARATION_RADIUS))
        {
            force.x += (**currentEnemy).getPosition().x - position.x;
            force.y += (**currentEnemy).getPosition().y - position.y;
            neighborCount++;
        }
  }

    if (neighborCount != 0) {
        force.x /= neighborCount;
        force.y /= neighborCount;
        //force.x *= -1;
       // force.y *= -1;
    }

    force = util->normalize(force);
    force *= MAX_SEPARATION;

    velocity = util->truncate(velocity + force, enemy.getMaxForce()*10.f);

    return velocity;
}




