#include "BarrierSimple.h"

BarrierSimple::BarrierSimple (const std::string& name,int nWaiting)
	: nWaiting(nWaiting), count(0), barrier(name,nWaiting) {}

void BarrierSimple::wait() {
	this->barrier.wait();
	this->count++;
	if (this->count == this->nWaiting) {

	}
}

void BarrierSimple::free() {
	this->count = 0;
	for (int i = 0; i <= nWaiting; ++i) {
		this->barrier.signal();
	}
}
