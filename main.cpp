#include "neurone.h"
#include <iostream>

int main() {
    Neuron neuron{0.1, 0.2, 0.3};
    //neuron.Xeq(1);
    //neuron.NullClina();
    neuron.Evolve(40);
}