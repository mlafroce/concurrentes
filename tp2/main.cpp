#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char** argv) {
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, 2);
	sigprocmask(SIG_BLOCK, &mask, 0);
	while (true) {
		printf("[%d] Durmiendo\n", getpid());
		sleep(10);
		execl("a.out", "a.out", (char*)0);	
	}
}
