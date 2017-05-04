#include "BarrierSimple.h"

BarrierSimple::BarrierSimple ( const std::string& name, char salt, int nWaiting )
    : nWaiting ( nWaiting ), count (name, salt),
      countMutex (name, salt, 1 ), turnstile (name, -salt, 0 ) {
		this->count.write(0);
}

BarrierSimple::~BarrierSimple() {
    if (count.numberOfAttachedProcesses() == 1) {
        countMutex.Delete();
        turnstile.Delete();
    }
}

void BarrierSimple::wait() {
    this->countMutex.wait();
    int localCount = this->count.read();
    localCount++;
    this->count.write ( localCount );
    if ( localCount == this->nWaiting ) {
        free();
    }
    localCount = this->count.read();
    this->countMutex.signal();
    this->turnstile.wait();
}

void BarrierSimple::free() {
    this->turnstile.signal(nWaiting);
    this->count.write(0);
}
