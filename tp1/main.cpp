#include <iostream>
#include <vector>
#include <cerrno>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
	int cantProcesos = atoi(argv[1]);
	
	std::cout << "Soy el Padre, mi PID es " << getpid() << std::endl;

	key_t key = ftok("/bin/bash", 69);
	size_t shm_size = cantProcesos * sizeof(int);
	uint permisos = 0644;
	int shmId = shmget(key, shm_size, IPC_CREAT | IPC_EXCL | permisos);
	if (shmId == -1) {
		std::cerr << "Falla shmget!" << std::cout;
		exit(errno);
	}

	std::vector<int> pidArray(cantProcesos);

	for (int i = 0; i < cantProcesos; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			std::cout << "Soy el hijo, tengo el PID " << getpid() << std::endl;
			int* sleepTimeArray = (int *) shmat(shmId, 0, 0);
			int returnValue = process();
			sleepTimeArray[i] = returnValue;
			shmdt(sleepTimeArray);
			exit(0);
		} else {
			pidArray[i] = pid;
		}
	}
	
	for (int i = 0; i < cantProcesos; i++) {
		waitpid(-1, 0, 0);
	}
	int* sleepTimeArray = (int *) shmat(shmId, 0, 0);
	for (int i = 0; i < cantProcesos; i++) {
		std::cout << "El hijo con PID " << pidArray[i] << " durmio " << sleepTimeArray[i] << " segundos." << std::endl;						
	}
	shmdt(sleepTimeArray);
	shmctl(shmId, IPC_RMID, 0);
	return 0;
}