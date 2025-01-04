#ifndef Neuron_Hpp
#define Neuron_Hpp

#include<iostream>
#include<vector>
#include "../Value/Value.hpp"

class Neuron {

    public :
        std::vector<Value*> w;
        Value *b;

    public :
        Neuron(int nin);

    public :
        Value* operator()(std::vector<Value*> &x);

        std::vector<Value*> parameters ();

};

#endif // Neuron_Hpp