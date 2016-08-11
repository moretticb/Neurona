#Intro

Neurona is an Arduino Library which allows boards to feed Artificial Neural Network (ANN) structures in order to perform tasks such as pattern recognition (classification), non-linear regression, function approximation and time-series prediction from the implemented architectures:

* Multi-Layer Perceptron (MLP) - [**training**][MLPTrainingLink]
* Perceptron (to be implemented)
* Learning Vector Quantization (LVQ-1 - to be implemented)

Check also [MorettiCB][MorettiCBBlog]'s blog (or simply click the *training* link which follows an architecture) to download and run the training mode of the aforementioned archictectures, so its outputs (the adjusted weights) can be used along with a specific network topology in operation mode.

This documentation encompasses the code reference and some examples, which can be easily accessed with through the left menu.

## Download and Installation

If you want to install Neurona, you can either search for Neurona in Arduino's Library Manager or download by clicking the button below:

[Download Neurona >][NeuronaDownloadLink]

[Click here][ArduinoLibInstallHelp] if you need aditional help in the installation step.

##Compatibility

The following list enumerates the boards which Neurona have been tested.

* Arduino Uno
* Arduino Mega

If your board is not here, it simply means it was not tested yet. You can also test Neurona in your board and send us a feedback through an [issue](https://github.com/MorettiCB/Neurona/issues) :)

## License

Neurona is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but **without any warranty**; without even the implied warranty of *merchantability* or *fitness for a particular purpose*. See the [GNU General Public License][GNULink] for more details.

[MLPTrainingLink]: http://www.moretticb.com/blog/multilayer-perceptron-implementation-in-c/
[MorettiCBBlog]: http://www.moretticb.com
[NeuronaDownloadLink]: http://www.github.com/MorettiCB/Neurona
[ArduinoLibInstallHelp]: http://www.arduino.cc/en/guide/libraries
[GNULink]: http://www.gnu.org/licenses/
