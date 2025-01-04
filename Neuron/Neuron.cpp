#include "Neuron.hpp"

Neuron::Neuron(int nin) {

    for (int i = 0; i < nin; ++i)
    {
        w.push_back(new Value(0.1));
    }

    this->b = new Value(0.2);
}

Value* Neuron::operator()(std::vector<Value*> &x) {
    Value *sum = new Value(0.0);
    Value *act = new Value(0.0);
    Value *out = new Value(0.0);

    for(int i = 0; i < x.size(); ++i) {

        act = *act + *this->w[i] * x[i];
    }

    act = *act + this->b;

    out = act->tanh();

    return out;
}

std::vector<Value*> Neuron::parameters() {
    std::vector<Value*> params;
    for(auto e : this->w) {
        params.push_back(e);
    }
    params.push_back(this->b);

    return params;
}