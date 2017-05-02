#ifndef PIPE_H
#define PIPE_H

#include <cstdlib>

class Pipe {
public:
	Pipe();
	~Pipe();
	Pipe(const Pipe& other) = delete;
	/**
	 * Send n bytes
	 */
	void write(const void* buffer, size_t bytes);
	/**
	 * Read n bytes
	 */
	void read(void* buffer, size_t bytes);
private:
	int fds[2];
};

#endif // PIPE_H
