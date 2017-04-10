#ifndef BARRIERSIMPLE_H
#define BARRIERSIMPLE_H

#include "Semaphore.h"

/**
 * Implementacion de una barrera simple basado en el molinete precargado del
 * libro "The Little book of semaphores v2.2.1"
 * Notar que es un molinete único, se necesitan dos para que la barrera pueda
 * ser reutilizada en un loop.
 */
class BarrierSimple {
public:
	BarrierSimple(int nWaiting);
	void wait();
	void free();
private:
	int nWaiting;
	int count;
	Semaphore countMutex;
	Semaphore turnstile;
};

#endif // BARRIERSIMPLE_H
