//////////////////////////////////////////////////////////////////////////////
//
//  MLP.h - Artificial Neural Network architectures for arduino
//  Copyright (c) 2016 Caio Benatti Moretti <caiodba@gmail.com>
//               http://www.moretticb.com/Neurona
//
//  Last update: 16 July 2016
//
//  This library is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef MLP_h
#define MLP_h

#include "Arduino.h"

/**
 * Multi-Layer Perceptron Artificial Neural Network.
 *
 * This Artificial Neural Network architecture can be used to perform classification, regression or time-series prediction.
 */
class MLP {
	public:
	
		/**
		 * Constructor.
		 * Initializes a Multi-Layer Perceptron (operation mode) from a trained topology with the adjusted synaptic weights, This network can be used for classification/regression.
		 * @param inputs the number of inputs to feed the network.
		 * @param outputs the number of network outputs.
		 * @param topology an array indicating the size of each layer (including outputs), ending with -1.
		 * @param activFunc the activation function to be used.
		 * @param weights an array with the adjusted weights (obtained in training).
		 * @param usingPGM whether weights is a PROGMEM variable.
		 * @see LOGISTIC
		 * @see TANH
		 * @see LINEAR
		 */
		MLP(byte inputs, byte outputs, int *topology, byte activFunc, double const *weights, boolean usingPGM);
		
		/**
		 * Logistic activation function
		 */
		static const byte LOGISTIC;
		
		/**
		 * Hyperbolic Tangent activation function
		 */
		static const byte TANH;
		
		/**
		 * Linear activation function
		 */
		static const byte LINEAR;
		
		double* forward(double *sample);
		int getActivation(double *sample);
		
	private:
		byte _inputs, _outputs, _layers, _iOffset, _yOffset, _activFunc;
		boolean _PGM;
		int* _layerSizes;
		double _inflection;
		double const * _initW;
		double* _iArray;
		double* _yArray;
				
		double activation(double x);
		double getWeight(int layer, int neuron, int weight, int inputs);
		double* getI(int inputs, int layer, double *sample);
		double* getY(int inputs, int layer, double *sample);
		
};

#endif