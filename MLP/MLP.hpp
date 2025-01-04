#ifndef MLP_Hpp
#define MLP_Hpp

#include<iostream>
#include<vector>
#include "../Value/Value.hpp"
#include "../Layer/Layer.hpp"

class MLP {

    public :
        std::vector<int> sz;
        std::vector<Layer> layers;

    public :
        MLP(std::vector<int> &nin, std::vector<int> &nouts);

    public : 
        Value* operator()(std::vector<Value*> x);

        std::vector<Value*> parameters();

};

#endif // MLP_Hpp