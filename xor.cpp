// Neural Network Driver
// Author: Amy Burnett
// Date:   January 30 2022
//========================================================================

#include <stdlib.h>
#include <stdio.h>
#include "matrix.hpp"
#include "neuralnet.hpp"

//========================================================================

int 
main ()
{
   
    printf ("Attempting to fit a neural network to the XOR problem\n");
    printf ("The XOR problem is sufficiently complex to need more than\n\
    one perceptron to solve. \n");
    printf ("============================================================\n");

    // 1 hidden node can only handle linear seperable 
    // problems so for AND that would be okay
    // but the XOR problem wouldnt work well 
    // even with 10,000 training cycles
    size_t num_input = 2; 
    size_t num_hidden = 10;
    size_t num_outputs = 1;

    printf ("Setting up Neural Network with\n\
    - %lu input nodes\n\
    - %lu hidden nodes\n\
    - %lu output nodes\n", num_input, num_hidden, num_outputs);
    
    NeuralNetwork nn (num_input, num_hidden, num_outputs);

    printf ("============================================================\n");

    // === TRAINING ======================================================

    printf ("Training model...\n");

    // XOR Problem
    float** trainingInputs = new float*[4] {
        new float[2] {0, 0},
        new float[2] {0, 1},
        new float[2] {1, 0},
        new float[2] {1, 1}
    };
    float** trainingOutputs = new float*[4] {
        new float[1] {0},
        new float[1] {1},
        new float[1] {1},
        new float[1] {0}
    };


    for (size_t i = 0; i < 100000; ++i) {
        int random_index = rand() % 4;
        nn.train(trainingInputs[random_index], trainingOutputs[random_index]);
    }

    printf ("============================================================\n");

    // === TESTING =======================================================

    printf ("Using Model to predict XOR results:\n");

    bool wasSuccessful = true; 
    printf ("predict([0,0]) -> ");
    float* outputs = nn.feedForward (new float[2] {0,0});
    printf ("%d\n", outputs[0] >= 0.5);
    if (outputs[0] >= 0.5) wasSuccessful = false;

    printf ("predict([1,0]) -> ");
    outputs = nn.feedForward (new float[2] {1,0});
    printf ("%d\n", outputs[0] >= 0.5);
    if (outputs[0] < 0.5) wasSuccessful = false;

    printf ("predict([0,1]) -> ");
    outputs = nn.feedForward (new float[2] {0,1});
    printf ("%d\n", outputs[0] >= 0.5);
    if (outputs[0] < 0.5) wasSuccessful = false;

    printf ("predict([1,1]) -> ");
    outputs = nn.feedForward (new float[2] {1,1});
    printf ("%d\n", outputs[0] >= 0.5);
    if (outputs[0] >= 0.5) wasSuccessful = false;

    printf ("Successful? ");
    if (wasSuccessful) printf ("yes\n");
    else printf ("no\n");



}

