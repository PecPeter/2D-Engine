#ifndef COLLTEST2D_HPP
#define COLLTEST2D_HPP

#include <cmath>
#include "mathVector.hpp"
#include "collShape2D.hpp"
#include "collObject.hpp"
#include "collPair.hpp"

// Given a cCollPair, this function will update the pair with collision
// information
void collTestHandler (cCollPair& collPair);
/*
cVector2 collTestPointPoint (const cCollObject2D& object1, const cCollObject2D& object2);
cVector2 collTestPointCircle (const cCollObject2D& object1, const cCollObject2D& object2);
cVector2 collTestPointAabb (const cCollObject2D& object1, const cCollObject2D& object2);
cVector2 collTestCircleCircle (const cCollObject2D& object1, const cCollObject2D& object2);
cVector2 collTestCircleAabb (const cCollObject2D& circleObj, const cCollObject2D& aabbObj);
*/
// This function return a vector, based on the state of the collision:
// NO COLLISION --> RETURN CVECTOR2(-1,-1)
// CONTACT      --> RETURN CVECTOR2(0,0)
// COLLISION    --> RETURN CVECTOR2(DX,DY)
// When a collision occurs, the returned vector is with respect to aabb1
cVector2 collTestAabbAabb (const cCollObject2D& aabb1, const cCollObject2D& aabb2);

#endif
