#include "Pipe.h"
#include <unistd.h>

Pipe::Pipe() {
	if (pipe(this->fds) == -1) {
		throw "Pipe failed";
	}
}

void Pipe::read(void* buffer, size_t bytes) {
	unsigned int readBytes = 0;
	while (readBytes < bytes) {
		readBytes += ::read(this->fds[0],
							static_cast<char*>(buffer) + readBytes,
							bytes - readBytes);
	}
}

void Pipe::write(const void* buffer, size_t bytes) {
	unsigned int writeBytes = 0;
	while (writeBytes < bytes) {
		writeBytes += ::write(this->fds[1],
							  static_cast<const char*>(buffer) + writeBytes,
							  bytes - writeBytes);
	}
}

Pipe::~Pipe() {
	close(this->fds[0]);
	close(this->fds[1]);
}
