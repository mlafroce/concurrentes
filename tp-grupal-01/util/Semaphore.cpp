#include <cstring>
#include "Semaphore.h"
#include "../log/Log.h"

Semaphore :: Semaphore (const std::string& name, char salt, const int initValue) :
	initValue(initValue) {
    key_t key = Utils::generateKey(name,salt);
	this->id = semget(key, 1, 0666 | IPC_CREAT );
	if (this->id < 0){
		THROW_UTIL( std::string("Error en semget() (crear): ") + std::string(strerror(errno)) );
	}
	this->init();
}

Semaphore::~Semaphore() {
}

int Semaphore::init() const {
	LOG_DEBUG("Iniciando semaforo con id: " + std::to_string(this->id));
	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->initValue;
	int result = semctl ( this->id,0,SETVAL,init );
	if (result < 0) {
		THROW_UTIL( std::string("Error en semctl(): ") + std::string(strerror(errno)) );
	}
	return result;
}

int Semaphore :: p () const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = -1;	// restar 1 al semaforo
	operation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operation,1 );
	if (result < 0) {
		THROW_UTIL( "Hubo un error al decrementar el semaforo (p)" + std::to_string(this->id) + " (" + std::string(strerror(errno)) + ")" );
	}
	return result;
}

int Semaphore :: v() const {
	return v(1);
}

int Semaphore :: v(int value) const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = (short)value;	// sumar al semaforo
	operation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operation,1 );
	if (result < 0) {
		THROW_UTIL( "Hubo un error al setear el semaforo (v[" + std::to_string(value) + "]) " + std::to_string(this->id) + " (" + std::string(strerror(errno)) + ")" );
	}
	return result;
}

int Semaphore::wait() const {
    return p();
}

int Semaphore::signal() const {
    return v();
}

int Semaphore::signal(int value) const {
    return v(value);
}

void Semaphore :: Delete () const {
	int result = semctl (this->id,0,IPC_RMID );
	if (result < 0) {
		THROW_UTIL( std::string("Error en semctl() (eliminar): ") + std::string(strerror(errno)) );
	}
}
