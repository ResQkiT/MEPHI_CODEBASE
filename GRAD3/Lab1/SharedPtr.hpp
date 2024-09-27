#include <iostream>
#include <vector>

template <typename T>
struct SharedData {
    T* ptr_;
    size_t shared_counter_;
    size_t weak_counter_;
};

template <typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
   public:
    SharedPtr() : data_(new SharedData<T>{.ptr_=new T(), .shared_counter_=1, .weak_counter_=0}) {
    }

    SharedPtr(const SharedPtr& other) : data_(other.data_) {
        ++data_->shared_counter_;
    }

    SharedPtr(T* ptr) : data_(new SharedData<T>{.ptr_=ptr, .shared_counter_=1, .weak_counter_=0}) {
    }

    SharedPtr(std::nullptr_t ptr) : data_((new SharedData<T>{.ptr_=ptr, .shared_counter_=1, .weak_counter_=0})){
    }

    ~SharedPtr() {
        --data_->shared_counter_;
        if (data_->shared_counter_ == 0 && data_->ptr_ != nullptr) {
            delete data_->ptr_;
            data_->ptr_ = nullptr;
        }
        if (data_->shared_counter_ + data_->weak_counter_ == 0) {
            delete data_;
        }
    }

    T& operator *() {
        return *data_->ptr_;
    }

    const T& operator *() const {
        return *data_->ptr_;
    }

    T* operator ->() {
        return data_->ptr_;
    }

    const T* operator ->() const {
        return data_->ptr_;
    }

    T* Get() {
        return data_->ptr_;
    }

    const T* Get() const {
        return data_->ptr_;
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other){
        if (this == &other || this->data_->ptr_ == other.data_->ptr_){
            return *this;
        }

        if (this->data_->ptr_ != nullptr) {
            this->data_->shared_counter_ = 0;
            this->data_->weak_counter_ = 0;
            delete this->data_->ptr_;
        }

        this->data_ = other.data_->ptr_;

        if (other.data_->ptr_ != nullptr) {
            this->data_->shared_counter_ = other.data_->shared_counter_;
            this->data_->shared_counter_ ++;
        } else {
            this->data_->shared_counter_ = 0;
        }
    }

    operator bool() const {
        return data_->ptr_ != nullptr;
    }

    bool operator==(const SharedPtr<T>& other){
        return data_ == other.data_;
    }

    bool operator!=(const SharedPtr<T>& other){
        return data_ != other.data_;
    }

    bool operator==(std::nullptr_t other){
        return !this;
    }

    bool operator!=(std::nullptr_t other){
        return this;
    }
private:
    SharedData<T>* data_;

    friend WeakPtr<T>;

    SharedPtr(SharedData<T>* data) : data_(data) {
        ++data_->shared_counter_;
    }
};

template <typename T>
class WeakPtr {
   public:
    WeakPtr(const SharedPtr<T> ptr) : data_(ptr.data_) {
        ++data_->weak_counter_;
    }

    WeakPtr(const WeakPtr& other) : data_(other.data_) {
        ++data_->weak_counter_;
    }

    ~WeakPtr() {
        --data_->weak_counter_;
        if (data_->shared_counter_ + data_->weak_counter_ == 0) {
            delete data_;
        }
    }

    SharedPtr<T> Lock() {
        return SharedPtr<T>(data_);
    }

    const SharedPtr<T> Lock() const {
        return SharedPtr<T>(data_);
    }

    size_t use_count() const{
        return this->data_->weak_counter_;
    }

    bool expired() const{
        return use_count() == 0;
    }

    //TODO: bool expired()
private:
    SharedData<T>* data_;
};

SharedPtr<int> Foo(int x) {
    SharedPtr<int> result;
    *result = x;
    return result;
}