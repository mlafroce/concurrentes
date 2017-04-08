#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
public:
	Thread();
	void start();
	void join();
	virtual ~Thread();
	virtual void run() = 0;
	Thread& operator=(Thread&& other);
	Thread(Thread&& other);
private:
	std::thread thread;
	Thread(const Thread &) = delete;
	Thread &operator=(const Thread &) = delete;
};

#endif // THREAD_H
