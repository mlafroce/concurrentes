#ifndef CONCURRENTES_SHAREDMEMORY_H
#define CONCURRENTES_SHAREDMEMORY_H

#include <string>

template <class T> class SharedMemory {
public:
    SharedMemory();
    void create(const std::string& file, const char letter);
    void attach();
    void detach();

private:
    int shmId;
    T* ptrData;

    SharedMemory( const std::string& file,const char letter);
    SharedMemory( const SharedMemory& other );

    void write( const T& data );
    T read() const;
    int numberOfAttachedProcesses() const;

    SharedMemory<T>& operator= ( const SharedMemory& other );

    ~SharedMemory ();
};


#endif //CONCURRENTES_SHAREDMEMORY_H
