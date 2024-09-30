#ifndef ROGUE_H
#define ROGUE_H
#include "../Player.h"

class Rogue : public Player {
public:
	Rogue();
	int SpecialAttack() override;
	void RestartInfo() override;
	void Die() override;
private:
};

#endif

