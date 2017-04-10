#include "BarrierSimple.h"

BarrierSimple::BarrierSimple (int nWaiting)
	: nWaiting(nWaiting), count(0), countMutex(1), turnstile(0) {}

void BarrierSimple::wait() {
	this->countMutex.wait();
	this->count++;
	if (this->count == this->nWaiting) {
		this->turnstile.signal(this->nWaiting);
		this->count = 0;
	}
	this->countMutex.signal();
	this->turnstile.wait();
}

void BarrierSimple::free() {
	this->turnstile.signal(this->nWaiting);
}
