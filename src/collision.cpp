#include "collision.h"

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B)
{
    if (A.x + A.w >= B.x && B.x + B.w >= A.x &&
        A.y + A.h >= B.y && B.y + B.h >= A.y)
    {
        return true;
    }
    return false;
}

//bool Collision::AABB(const ColliderComponent& A, const ColliderComponent& B)
//{
//    if (AABB(A.collider, B.collider))
//    {
//        std::cout << A.tag << " hit:" << B.tag << std::endl;
//        return true;
//    }
//    return false;
//}
