#include "LinkedList.hpp"
#include <string>

template<class T>
class Adapter : public AdapterBase<T>{
private:
    LinkedList<T> list;
public:
    Adapter() : list{}
    {}
    ~Adapter() = default;

    void append(const T & value) override {
        list.push_back(value);
    }
    void prepend(const T & value){
        list.prepend(value);
    }
    void insert(size_t index, T & value){
        list.insert_at(value, index);
    }
    T& get(size_t index){
        return list.get(index);
    }
    T& getFirst(){
        return list.front();
    }
    T& getLast(){
        return list.back()
    }
    size_t get_size(){
        return list.size();
    }   
    std::string raw_string(){
        std::string answer = "";
        for (size_t i = 0; i < list.size(); i++)
        {
            answer += list.get(i);   
        }
        return answer;
    }
};