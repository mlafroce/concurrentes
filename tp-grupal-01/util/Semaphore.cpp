#include "Semaphore.h"

Semaphore :: Semaphore ( const std::string& name,const int initValue ):initValue(initValue) {
	key_t key = ftok ( name.c_str(),'a' );
	this->id = semget ( key,1,0666 | IPC_CREAT );

	this->init ();
}

Semaphore::~Semaphore() {
}

int Semaphore :: init () const {

	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->initValue;
	int result = semctl ( this->id,0,SETVAL,init );
	return result;
}

int Semaphore :: p () const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = -1;	// restar 1 al semaforo
	operation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operation,1 );
	return result;
}

int Semaphore :: v () const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = 1;	// sumar 1 al semaforo
	operation.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operation,1 );
	return resultado;
}

void Semaphore :: Delete () const {
	semctl ( this->id,0,IPC_RMID );
}
