#ifndef Value_Hpp
#define Value_Hpp

#include<iostream>
#include<vector>
#include<functional>

class Value {

    // member variables

    public :
        double data = 0.0;
        std::vector<std::vector<Value*>> _prev;
        std::string _op;
        double grad = 0.0;
        

    // constructor

    public :
        Value();
        Value(double data, std::vector<Value*> _children={}, std::string _op="");

    // member functions

    public : 
        friend std::ostream& operator<<(std::ostream &os, const Value v);

        Value* operator+(Value *other);

        Value* operator-(Value *other);

        Value* operator*(Value *other);

        Value* tanh();

        void backward();

        std::function<void()> _backward = nullptr;

};

#endif // Value_Hpp