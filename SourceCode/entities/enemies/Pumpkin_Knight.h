#ifndef PUMPKIN_KNIGHT_H
#define PUMPKIN_KNIGHT_H
#include "../Enemy.h"

class Pumpkin_Knight : public Enemy {
private:
public:
	Pumpkin_Knight();
	void Appear()override;
	void Die()override;
};

#endif

