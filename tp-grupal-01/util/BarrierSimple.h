#ifndef BARRIERSIMPLE_H
#define BARRIERSIMPLE_H

#include "Semaphore.h"
#include "SharedMemory.h"

class BarrierSimple {
public:
	BarrierSimple(const std::string& name, char salt, int nWaiting);
	void wait();
	void free();
private:
	int nWaiting;
	SharedMemory<int> count;
	Semaphore turnstile;
	Semaphore countMutex;
};

#endif // BARRIERSIMPLE_H
