#ifndef SKELETON_H
#define SKELETON_H
#include "../Enemy.h"

class Skeleton : public Enemy {
private:
public:
	Skeleton();
	void Appear()override;
	void Die()override;
};

#endif

