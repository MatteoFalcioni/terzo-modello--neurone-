#include "neurone.h"
#include <iostream>

int main() {
    Neuron neuron{0.1, 0.25, 0.3};  // V, I, W
    neuron.Evolve(60);
    //neuron.Xeq(0);
    //neuron.NullClina();
}