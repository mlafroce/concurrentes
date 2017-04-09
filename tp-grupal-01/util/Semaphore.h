#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

class Semaphore {
public:
	Semaphore(unsigned int initValue);
	void signal();
	void wait();
	virtual ~Semaphore();
	Semaphore(Semaphore&& other);
	Semaphore& operator=(Semaphore&& other);
private:
	sem_t sem;
	Semaphore(const Semaphore &) = delete;
	Semaphore &operator=(const Semaphore &) = delete;
};

#endif //SEMAPHORE_H
