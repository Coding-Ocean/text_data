#pragma once
#include<string>
template<typename T>
class DATA_TYPE
{
    T Data;
    std::string Name;
public:
    void set(const char* name, T data) {
        Data = data;
        Name = name;
    }
    T data() {return Data;}
    std::string& name() { return Name; }
};

