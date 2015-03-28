#include "Collision.h"
#include <iostream>

using namespace cocos2d;
using namespace std;

bool CollisionManager::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == WALL)
        {
	  cout << "OPA" << endl;
        }
        else if (nodeB->getTag() == WALL)
        {
	  cout << "OPA" << endl;
        }
    }

    return true;
}
