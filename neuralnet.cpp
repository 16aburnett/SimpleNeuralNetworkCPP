// Simple Neural Network Library 
// Author: Amy Burnett
// Date:   January 30 2022
//========================================================================

#include <math.h> 
#include "matrix.hpp"
#include "neuralnet.hpp"

//========================================================================

const double EULER = 2.71828182845904523536;

// ACTIVATION FUNCTION
// sigmoid:
// 1 / (1 + e^-x)
float sigmoid(float x){
    return (1) / (1 + pow (EULER, -x));
}

// derivative of sigmoid 
// this is not the full derivative because 
// it is used after sigmoid is already applied
// dsigmoid(x) = sigmoid(x) / (1 - sigmoid(x));
float dsigmoid(float x){
    return (x * (1 - x));
}

//========================================================================

// Constructs the neural network
// params - input, hidden, output
NeuralNetwork::NeuralNetwork (size_t inputCount, size_t hiddenCount, size_t outputCount){

    m_inputCount = inputCount;
    m_hiddenCount = hiddenCount;
    m_outputCount = outputCount;

    // weights 
    m_weights_ih = Matrix (hiddenCount, inputCount);
    m_weights_ih.randomize();
    m_weights_ho = Matrix (outputCount, hiddenCount);
    m_weights_ho.randomize();

    // bias
    // one bias for each layer
    // connected to each of the next layer
    m_bias_ih = Matrix (hiddenCount, 1);
    m_bias_ih.randomize();
    m_bias_ho = Matrix (outputCount, 1);
    m_bias_ho.randomize();
    
    // previous node values 
    m_hidden_nodes;
    m_output_nodes;

    m_learning_rate = 0.1;

}

//========================================================================

// Feed Forward Algorithm
// Feeds input through neural network to arive at an output
// param inputs - must be an array of desired inputs. (must be size of inputCount)
float* NeuralNetwork::feedForward(float* inputsArr){

    // Ensure inputs are valid 
    if(!inputsArr){
        printf("error: please enter a valid array of input\n");
        return nullptr;
    } 

    // convert input array to column matrix 
    Matrix input_nodes = Matrix::fromArray(inputsArr, m_inputCount, SINGLE_COLUMN);

    // Input to Hidden Feed
    // activation(weights * inputs + bias)
    m_hidden_nodes = Matrix::product(m_weights_ih, input_nodes); // weighted sum
    m_hidden_nodes.add(m_bias_ih);// adding bias
    m_hidden_nodes.map(sigmoid); // applying activation function


    // Hidden to Output Feed
    m_output_nodes = Matrix::product(m_weights_ho, m_hidden_nodes);// weighted sum
    m_output_nodes.add(m_bias_ho); // adding bias
    m_output_nodes.map(sigmoid); // applying activation function

    // convert output into array 
    float* output = m_output_nodes.toArray();
    return output;

}

//========================================================================

// TRAINING NEURAL NETWORK
// feeds forward a given input
// changes weights if output doesnt match given expected answer 
// uses stochastic gradient descent - alters weights after each feed forward
void NeuralNetwork::train(float* inputs_arr, float* answers_arr){

    // Convert params to matrices 
    Matrix inputs = Matrix::fromArray(inputs_arr, m_inputCount, SINGLE_COLUMN);
    Matrix outputs = Matrix::fromArray(feedForward(inputs_arr), m_outputCount, SINGLE_COLUMN);
    Matrix answers = Matrix::fromArray(answers_arr, m_outputCount, SINGLE_COLUMN);

    // calculate error <output>
    // error = answer - output
    Matrix output_errors = Matrix::subtract(answers, outputs);

    // Calculate Hidden Errors (hidden -> output)
    Matrix weights_ho_t = Matrix::transpose(m_weights_ho);
    Matrix hidden_errors = Matrix::product(weights_ho_t, output_errors);

    // Calculate Change in Weights hidden -> output
    Matrix hidden_gradients = Matrix::multiply(output_errors, Matrix::map(outputs, dsigmoid));
    Matrix hidden_nodes_t = Matrix::transpose(m_hidden_nodes);
    Matrix delta_weights_ho = Matrix::product(hidden_gradients, hidden_nodes_t);
    delta_weights_ho.multiply(m_learning_rate);
    Matrix delta_bias_ho = Matrix::multiply(hidden_gradients, m_learning_rate);

    // Change weights
    m_weights_ho.add(delta_weights_ho);
    m_bias_ho.add(delta_bias_ho);

    // Calculate Change in Weights input -> hidden
    Matrix input_gradients = Matrix::multiply(hidden_errors, Matrix::map(m_hidden_nodes, dsigmoid));
    Matrix input_nodes_t = Matrix::transpose(inputs);
    Matrix delta_weights_ih = Matrix::product(input_gradients, input_nodes_t);
    delta_weights_ih.multiply(m_learning_rate);
    Matrix delta_bias_ih = Matrix::multiply(input_gradients, m_learning_rate);

    // Change weights
    m_weights_ih.add(delta_weights_ih);
    m_bias_ih.add(delta_bias_ih);

}
    

//========================================================================
