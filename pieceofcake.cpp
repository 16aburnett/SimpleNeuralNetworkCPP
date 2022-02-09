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
   
    printf ("============================================================\n");

    // 1 hidden node can only handle linear seperable 
    // problems so for AND that would be okay
    // but the XOR problem wouldnt work well 
    // even with 10,000 training cycles
    size_t num_input = 3; 
    size_t num_hidden = 30;
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
        new float[3] {10/10000, 4/10000, 7/10000},
        new float[3] { 5/10000, 2/10000, 2/10000},
        new float[3] { 4/10000, 2/10000, 1/10000},
        new float[3] { 100/10000, 10/10000, 1000/10000},
    };
    float** trainingOutputs = new float*[4] {
        new float[1] {168/10000},
        new float[1] {36/10000},
        new float[1] {24/10000},
        new float[1] {360000/10000}

    };


    for (size_t i = 0; i < 100000; ++i) {
        int random_index = rand() % 4;
        nn.train(trainingInputs[random_index], trainingOutputs[random_index]);
    }

    printf ("============================================================\n");

    // === TESTING =======================================================

    printf ("Using model to predict:\n");

    printf ("predict([10, 4, 7]) -> ");
    float* outputs = nn.feedForward (new float[3] {10, 4, 7});
    printf ("%f\n", outputs[0]*10000);

    printf ("predict([5, 2, 2]) -> ");
    outputs = nn.feedForward (new float[3] {5, 2, 2});
    printf ("%f\n", outputs[0]*10000);
    
    printf ("predict([4, 2, 1]) -> ");
    outputs = nn.feedForward (new float[3] {4, 2, 1});
    printf ("%f\n", outputs[0]*10000);


}

