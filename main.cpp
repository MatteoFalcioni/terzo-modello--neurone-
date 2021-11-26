#include "neurone.h"
#include <iostream>

int main() {
    Neuron neuron{0.1, 0.2, 0.3};
    neuron.Evolve(40);
    //neuron.Xeq(0);
    //neuron.NullClina();
}