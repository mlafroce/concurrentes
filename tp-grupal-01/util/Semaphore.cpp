#include <iostream>
#include "Semaphore.h"

// Sem type 0 para threads, otro para procesos
Semaphore::Semaphore (unsigned int initValue) {
	int retValue = sem_init(this->sem, 0, initValue);
}

Semaphore::~Semaphore() {
	sem_destroy(&this->sem);
}

void Semaphore::signal() {
	sem_post(&this->sem);
}

void Semaphore::wait() {
	sem_wait(&this->sem);
}
