#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"

bool CollisionManager::hasHit(GameObject* obj1, GameObject* obj2)
{
    //Checks the current distance between 2 objects

    float x1, y1, x2, y2;

    obj1->GetSprite()->GetPosition(x1, y1);
    obj2->GetSprite()->GetPosition(x2, y2);

    float xComp = (x1 - x2) * (x1 - x2);
    float yComp = (y1 - y2) * (y1 - y2);

    float objectSeparation = sqrtf(xComp + yComp);

    return (objectSeparation < (obj1->ObjectRadius + obj2->ObjectRadius)) ? true : false; ;
}

bool CollisionManager::hasHitAABB(GameObject* obj1, GameObject* obj2)
{
    float x1, y1, x2, y2;

    obj1->GetSprite()->GetPosition(x1, y1);
    obj2->GetSprite()->GetPosition(x2, y2);

    if (abs(x1 - x2) > (obj1->ObjectRadius + obj2->ObjectRadius)) return false;
    if (abs(y1 - y2) > (obj1->ObjectRadius + obj2->ObjectRadius)) return false;

    return true;
}