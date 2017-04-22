#ifndef BARRIERSIMPLE_H
#define BARRIERSIMPLE_H

#include "Semaphore.h"

class BarrierSimple {
public:
	BarrierSimple(const std::string& name,int nWaiting);
	void wait();
	void free();
private:
	int nWaiting;
	int count;
	Semaphore barrier;
};

#endif // BARRIERSIMPLE_H
