#include<iostream>
#include<vector>
#include "Value/Value.hpp"
#include "MLP/MLP.hpp"

int main(int argc, char *argv[]) {

    std::vector<int> nin = {3}; 
    std::vector<int> nouts = {4, 4, 1};
    MLP m(nin, nouts);

    std::vector<std::vector<Value*>> xs = {
                                         {new Value(2.0), new Value(3.0), new Value(-1.0)},
                                         {new Value(3.0), new Value(-1.0), new Value(0.5)},
                                         {new Value(0.5), new Value(1.0), new Value(1.0)},
                                         {new Value(1.0), new Value(1.0), new Value(-1.0)}
    };

    std::vector<Value*> ys = {new Value(1.0), new Value(-1.0), new Value(-1.0), new Value(1.0)};

    Value *step = new Value(0.1);
    Value *loss = new Value(0.0);
    std::vector<Value*> ypred;
    std::vector<Value *> lossarray;

    for(int i = 0; i < 20; ++i) {

        for(auto x : xs) {
            ypred.push_back(m.operator()(x));
        }

        for(int j = 0; j < ys.size(); ++j) {
            Value *a1 = *ypred[j] - ys[j];
            lossarray.push_back(*a1 * a1);
        }

        for(auto e : lossarray)
            loss = *loss + e;

        for(auto p : m.parameters()) {
            p->grad = 0.0;
        }

        loss->backward();

        for(auto p : m.parameters()) {
            p->data = p->data - 0.1 * p->grad;
        }

        lossarray.clear();
        ypred.clear();
        std::cout<<"Loss : "<<*loss<<std::endl;
        loss = new Value(0.0);

    }

    return 0;
}