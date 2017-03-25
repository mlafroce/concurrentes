#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WAIT_TIME 10

long int random() {
	srand(getpid());
	long int result = rand() % WAIT_TIME;
	return result;
}

int process() {
	int sleep_time = random();
	std::cout << "Voy a dormir " << sleep_time << " segundos." << std::endl;
	sleep(sleep_time);
	return sleep_time;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Falta parametro: cant de procesos." << std::endl;
		return 0;
	}
	int cant_procesos = atoi(argv[1]);
	
	std::cout << "Soy el Padre, mi PID es " << getpid() << std::endl;

	for (int i = 0; i < cant_procesos; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			std::cout << "Soy el hijo, tengo el PID " << getpid() << std::endl;
			int returnValue = process();
			exit(returnValue);
		}
	}
	
	int retornoHijo = 0;
	for (int i = 0; i < cant_procesos; i++) {
		pid_t childPid = waitpid(-1, &retornoHijo, 0);
		int sleepTime = WEXITSTATUS(retornoHijo);
		std::cout << "El hijo con PID " << childPid << " durmio " << sleepTime << " segundos." << std::endl;
	}
	return 0;
}