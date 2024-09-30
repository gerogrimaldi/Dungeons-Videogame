#ifndef ORC_H
#define ORC_H
#include "../Enemy.h"

class Orc : public Enemy {
private:
public:
	Orc();
	void Appear()override;
	void Die()override;
};

#endif

