#ifndef KNIGHT_H
#define KNIGHT_H
#include "../Player.h"

class Knight : public Player {
public:
	Knight();
	int SpecialAttack() override;
	void RestartInfo() override;
	void Die() override;
private:
};

#endif

