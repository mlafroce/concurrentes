#ifndef CONCURRENTES_SHAREDMEMORY_H
#define CONCURRENTES_SHAREDMEMORY_H

#include <string>


class SharedMemoryBase {
public:
    int numberOfAttachedProcesses() const;
protected:
	SharedMemoryBase(int shmid);
	SharedMemoryBase(int shmid, void* ptrData);
	~SharedMemoryBase();
	int shmId;
	void* ptrData;
	void create(const std::string& file, const char letter, size_t dataSize);
	void attach();
	void detach();
};

template<class T>
class SharedMemory : public SharedMemoryBase {
public:
	SharedMemory(const std::string& file,const char letter) :
		SharedMemoryBase(0, nullptr) {
		this->create(file, letter);
	}
	
    SharedMemory(const SharedMemory& other) : SharedMemoryBase(other.shmId) {
		this->attach();
	}

    void write(const T& data ) {
		*static_cast<T*>(this->ptrData) = data;
	}

	T read() const {
		return *static_cast<T*>(this->ptrData);
	}

    SharedMemory& operator= (const SharedMemory& other){
		this->shmId = other.shmId;
		this->attach();
		return *this;
	}

private:
    SharedMemory() = delete;
	void create(const std::string& file, const char letter) {
		SharedMemoryBase::create(file, letter, sizeof(T));
	}
};


#endif //CONCURRENTES_SHAREDMEMORY_H
