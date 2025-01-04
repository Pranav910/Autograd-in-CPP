#include "Value.hpp"
#include<iostream>
#include<cmath>
#include<set>

Value::Value() {}

Value::Value(double data, std::vector<Value*> _children, std::string _op) {
    this->data = data;
    this->_prev.push_back(_children);
    this->_op = _op;
}

Value* Value::operator+(Value *other) {

    Value *out = new Value(this->data + other->data, {this, other}, "+");

    out->_backward = [this, other, out]() {
        this->grad += 1.0 * out->grad;
        other->grad += 1.0 * out->grad;
    };


    return out;
}

Value* Value::operator*(Value *other) {
    Value *out = new Value(this->data * other->data, {this, other}, "*");

    out->_backward = [this, other, out]() {
        this->grad += other->data * out->grad;
        other->grad += this->data * out->grad;
    };

    return out;
}

Value* neg(Value *v) {
    Value *nv = new Value(-1.0);
    v = *v * nv;
    return v;
}

Value* Value::operator-(Value *other) {
    
    other = neg(other);
    return *this + other;
}


Value* Value::tanh() {
    double x = this->data;
    double t = (exp(2 * x) - 1) / (exp(2 * x) + 1);
    Value *out= new Value(t, {this, }, "tanh");

    auto _backward = [this, t, out]() {
        this->grad = (1 - t * t) * out->grad;
    };

    out->_backward = _backward;

    return out;
}


void build_topo(Value& v, std::vector<Value*>& topo, std::set<Value*>& visited) {
    if (visited.find(&v) == visited.end()) {
        visited.insert(&v);
        
        for (auto& sub_vector : v._prev) {
            for (Value* child : sub_vector) { 
                build_topo(*child, topo, visited);
            }
        }
        topo.push_back(&v);
    }
}

void Value::backward() {
    std::vector<Value*> topo;
    std::set<Value*> visited;

    build_topo(*this, topo, visited);

    this->grad = 1.0;

    for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
        if ((*it)->_backward != nullptr) {
            (*it)->_backward();
        }
    }
}

std::ostream& operator<<(std::ostream &os, const Value v) {
    os << "Value(data=" << v.data << ")";
    return os;
}