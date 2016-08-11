#Reference

## MLP

The Multi-Layer Perceptron ANN Architecture. This architecture can be used to perform classification, regression, function approximation or time-series prediction.

###MLP()

Initializes an MLP (operation mode) architecture from a [trained][MLPTrainingLink] topology with the adjusted synaptic weights.

####Syntax

```cpp
MLP(inputs, outputs, topology, activFunc, weights, usingPGM);
```

####Parameters
* ```inputs``` is the number of inputs to feed the network.
* ```outputs``` is the number of network outputs.
* ```topology``` is an array indicating the size of each layer (including ```outputs```), ending with -1.
* ```activFunc``` indicates the activation function to be used.
* ```weights``` is an array with the adjusted weights (obtained in [training][MLPTrainingLink]).
* ```usingPGM``` flags whether ```weights``` is a [PROGMEM][ArduinoPROGMEM] variable.

####Example

```cpp
double PROGMEM const initW[] = {2.753086, -11.472257 , ... , 4.524327};
int topology[]={6,10,-1};

// Initializing an MLP neural network with 3 inputs,
// 10 outputs and two neural layers with 6 (hidden) and 10 (output) neurons:
MLP mlp(3,10,topology,MLP::LOGISTIC,initW,true);
```

####See also

* [Constants](#reference-mlp-constants)

###forward()

Feeds the network with a provided input array and outputs the activation of the neurons at the output layer.

####Returns

double[]: an ```output```-sized array with the output of the neurons at the output layer

####Syntax

```cpp
mlp.forward(instance)
```

####Parameters

* ```mlp``` is the initialized MLP network
* ```instance``` is the input array to feed the network

####Example

```cpp
//The first instance input should be always -1 for the bias
double instance[] = {-1.0, 1.0, 1.0, 0.0};
double *out = mlp.forward(instance);
```

####See also
* [getActivation()](#reference-mlp-getactivation)

###getActivation()

Feeds the network with a provided input array and outputs the index of the highest activation, i.e., the neuron with the highest output.

####Returns

int: the index of the neuron with the highest output

####Syntax

```cpp
mlp.getActivation(instance)
```

####Parameters

* ```mlp``` is the initialized MLP network
* ```instance``` is the input array to feed the network

####Example

```cpp
//The first instance input should be always -1 for the bias
double instance[] = {-1.0, 1.0, 1.0, 0.0};
int index = mlp.getActivation(instance);
```

####See also
* [forward()](#reference-mlp-forward)

###Constants

The following list enumerate constants related to activation functions:

* Sigmoidal functions
	* ```MLP::LOGISTIC``` = ```0``` - Logistic function (from 0 to 1)
	* ```MLP::TANH``` = ```1``` - Hyperbolic Tangent function (from -1 to 1)
* Other functions
	* ```MLP::LINEAR``` = ```2``` - Linear function

[MLPTrainingLink]: http://www.moretticb.com/blog/multilayer-perceptron-implementation-in-c/
[ArduinoPROGMEM]: https://www.arduino.cc/en/Reference/PROGMEM