#include "MLP.hpp"

MLP::MLP(std::vector<int> &nin, std::vector<int> &nouts) {
    this->sz.insert(sz.end(), nin.begin(), nin.end());
    this->sz.insert(sz.end(), nouts.begin(), nouts.end());

    for(int i = 0; i < nouts.size(); ++i) {
        this->layers.push_back(Layer(sz[i], sz[i + 1]));
    }

}

Value* MLP::operator()(std::vector<Value*> x) {

    std::vector<Value> x2;
    int i = 0;

    for(auto layer : this->layers) {

        x = layer.operator()(x);
    }

    return x[0];
}

std::vector<Value*> MLP::parameters() {

    std::vector<Value*> params;

    for(auto layer : this->layers) {
        for(auto p : layer.parameters()) {
            params.push_back(p);
        }
    }

    return params;
}