#ifndef Layer_Hpp
#define Layer_Hpp

#include<iostream>
#include<vector>
#include "../Neuron/Neuron.hpp"
#include "../Value/Value.hpp"

class Layer {

    public :
        std::vector<Neuron> neurons;

    public :
        Layer(int nin, int nout) ;

    public :
        std::vector<Value*> operator()(std::vector<Value*> x);

        std::vector<Value*> parameters();

};

#endif // Layer_Hpp