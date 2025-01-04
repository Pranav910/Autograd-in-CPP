#include "Layer.hpp"

Layer::Layer(int nin, int nout) {

    for(int i = 0; i < nout; ++i) {
        this->neurons.push_back(Neuron(nin));
    }

}

std::vector<Value*> Layer::operator()(std::vector<Value*> x) {

    std::vector<Value*> outs;

    for(auto n : this->neurons) {
        outs.push_back(n.operator()(x));
    }
    
    return outs;
}

std::vector<Value*> Layer::parameters() {
    std::vector<Value*> params;

    for(auto neuron : this->neurons) {
        for(auto p : neuron.parameters()) {
            params.push_back(p);
        }
    }

    return params;
}