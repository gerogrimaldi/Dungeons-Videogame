#ifndef MAGE_H
#define MAGE_H
#include "../Player.h"

class Mage : public Player {
public:
	Mage();
	int SpecialAttack() override;
	void RestartInfo() override;
	void Die() override;
private:
};

#endif

