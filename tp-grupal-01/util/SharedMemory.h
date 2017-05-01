#ifndef CONCURRENTES_SHAREDMEMORY_H
#define CONCURRENTES_SHAREDMEMORY_H

#include <string>

template <class T> class SharedMemory {
private:
    int shmId;
    T* ptrData;

    SharedMemory();
    void create(const std::string& file, const char letter);
    void attach();
    void detach();

    int numberOfAttachedProcesses() const;

public:
    SharedMemory( const std::string& file,const char letter);

    SharedMemory( const SharedMemory& other );
    void write( const T& data );
    T read() const;

    SharedMemory<T>& operator= ( const SharedMemory& other );

    ~SharedMemory ();
};


#endif //CONCURRENTES_SHAREDMEMORY_H
