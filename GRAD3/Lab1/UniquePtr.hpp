#pragma once
#include <functional>

template<class T>
class UniquePtr{
public: 
    
    UniquePtr(T * data, std::function<void(T*)> callback = [](T* obj){delete obj;}) 
    : data{data}, callback{callback}
    {}

    ~UniquePtr(){
        callback(data);
    }

    UniquePtr(const UniquePtr & other) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

    T* operator->(){
        return data;
    }

    const T* operator->(){
        return data;
    }

    T& operator*(){
        return *data;
    }

    const T& operator*(){
        return *data;
    }

private:
    T * data;

    std::function<void(T*)> callback;
};