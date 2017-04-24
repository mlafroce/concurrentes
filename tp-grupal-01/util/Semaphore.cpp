#include "Semaphore.h"
#include "../Log/Log.h"

Semaphore :: Semaphore (const std::string& name, char salt, const int initValue) :
	initValue(initValue) {
	//TODO: atrapar errores!
    key_t key = ftok (name.c_str(), salt);
	this->id = semget(key, 1, 0666 | IPC_CREAT );
	this->init ();
}

Semaphore::~Semaphore() {
}

int Semaphore::init() const {
	LOG_INFO("Iniciando semaforo");
	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->initValue;
	int result = semctl ( this->id,0,SETVAL,init );
	if (result) {
		LOG_INFO("Hubo un error al setear el semaforo" + std::to_string(this->id));
	}
	return result;
}

int Semaphore :: p () const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = -1;	// restar 1 al semaforo
	operation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operation,1 );
	if (result)
		LOG_INFO("Hubo un error al decrementar el semaforo" + std::to_string(this->id));
	return result;
}

int Semaphore :: v() const {
	v(1);
}

int Semaphore :: v(int value) const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = value;	// sumar al semaforo
	operation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operation,1 );
	if (result) {
		LOG_INFO("Hubo un error al setear el semaforo" + std::to_string(this->id));
	}
	return result;
}

int Semaphore::wait() const {
    p();
}

int Semaphore::signal() const {
    v();
}

int Semaphore::signal(int value) const {
    v(value);
}

void Semaphore :: Delete () const {
	semctl (this->id,0,IPC_RMID );
}
