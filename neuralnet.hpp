// Simple Neural Network Library 
// Author: Amy Burnett
// Date:   January 30 2022
//========================================================================

#ifndef NEURALNET_HPP
#define NEURALNET_HPP

//========================================================================

#include "matrix.hpp"

//========================================================================


class NeuralNetwork
{

public:
    size_t m_inputCount; 
    size_t m_hiddenCount; 
    size_t m_outputCount;

    // hiddenCount x inputCount
    Matrix m_weights_ih;
    // outputCount x hiddenCount 
    Matrix m_weights_ho;
    // bias
    // one bias for each layer
    // connected to each of the next layer
    // hiddenCount x 1 
    Matrix m_bias_ih;
    // outputCount x 1
    Matrix m_bias_ho;

    // previous node values 
    Matrix m_hidden_nodes; 
    Matrix m_output_nodes; 

    float  m_learning_rate = 0.1;

    // Constructs the neural network
    // params - input, hidden, output
    NeuralNetwork (size_t inputCount, size_t hiddenCount, size_t outputCount);

    // Feed Forward Algorithm
    // Feeds input through neural network to arive at an output
    // param inputs - must be an array of desired inputs. (must be size of inputCount)
    float* feedForward(float* inputsArr);

    // TRAINING NEURAL NETWORK
    // feeds forward a given input
    // changes weights if output doesnt match given expected answer 
    // uses stochastic gradient descent - alters weights after each feed forward
    void train(float* inputs_arr, float* answers_arr);
    
};

//========================================================================

#endif 