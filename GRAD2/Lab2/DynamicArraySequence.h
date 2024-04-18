#include "Sequence.h"
#include "DynamicArray.h"

template<class T>
class DynamicArraySequence : public Sequence<T>
{
    private:
    DynamicArray<T> * impl;
public:
    DynamicArraySequence(){
        
    }

    T getFirst(){
        return this->impl->front();
    }
    T getLast(){
        return this->impl->back();
    }
    T get(size_t index){
        return this
    }
    Sequence<T> getSubsequence(size_t startIndex, size_t endIndex){

    }
    size_t getLength(){

    }
    void append(T item){

    }
    void prepend(T item){

    }
    void insertAt(size_t index, T item){
    
    }
    Sequence<T> concat(Sequence<T> * list){

    }
};
