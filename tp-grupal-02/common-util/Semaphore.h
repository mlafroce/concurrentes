#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaphore {

private:
	int id;
	int initValue;

	int init() const;

public:
	Semaphore (const std::string& name, char salt, const int initValue );
    ~Semaphore();

	int p () const; // decrementa
	int v () const; // incrementa
	int v(int value) const;
    int wait() const;
    int signal() const;
	int signal(int value) const;
	void Delete () const;
};

#endif //SEMAPHORE_H
