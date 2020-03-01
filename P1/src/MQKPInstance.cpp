/*
 * MQKPInstance.cpp
 *
 * File defining the methods of the class MQKPInstance.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPInstance.h"
#include "MQKPSolution.h"
#include <fstream>
#include <string>

#include <iostream>

MQKPInstance::MQKPInstance()
    : _numKnapsacks(0)
    , _numObjs(0)
    , _profits(NULL)
    , _weights(NULL)
    , _capacities(NULL)
{
}

MQKPInstance::~MQKPInstance()
{
    //DONE complete
    delete[] _weights;
    delete[] _capacities;

    for (auto i = 0; i < _numObjs; ++i) {
        delete[] _profits[i];
    }

    delete[] _profits;
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution& solution)
{

    double* sumWeights = new double[this->_numKnapsacks + 1];

    for (int j = 1; j <= this->_numKnapsacks; j++) {
        sumWeights[j] = 0;
    }

    for (int i = 0; i < this->_numObjs; i++) {

        /*DONE Complete
		 * 1. Obtain the knapsack where we can find the i-th object.
		 * 2. If it is a valid knapsack (higher than 0), increment sumWeights by the weight of the object.
		 */
        if (solution.whereIsObject(i) != 0)
            sumWeights[solution.whereIsObject(i)] += this->getWeights()[i];
    }

    double maxCapacityViolation = 0; //We initialize maximum violation to 0, meaning that there are no violations.

    for (int j = 1; j <= this->_numKnapsacks; j++) {

        /*DONe Complete
		 * 1. Obtain the violation for the j-th knapsack
		 * 2. Update maxCapacityViolation if needed
		 */
        double violation = sumWeights[j] - getCapacities()[j];
        if (violation > maxCapacityViolation)
            maxCapacityViolation = violation;
    }

    delete[] sumWeights;
    return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution& solution)
{

    double sumProfits = 0.;

    /*DONE Complete
    * Double loop for each pair of objects
    * Any object included in any knapsack (> 0) must sum its individual profit.
    * Any pair of objects included in the same knapsack (and with value > 0) must sum its shared profit.
    *      IMPORTANT NOTE, sum the pair (i,j) only once, that is, if you sum (i, j), you should not sum (j, i)
    */
    for (int i = 0; i < getNumObjs(); ++i) {
        if (solution.whereIsObject(i) != 0) {
            sumProfits += getProfits()[i][i];
            for (int j = i + 1; j < getNumObjs(); ++j) {
                if (solution.whereIsObject(j) == solution.whereIsObject(i))
                    sumProfits += getProfits()[i][j];
            }
        }
    }
    return sumProfits;
}

void MQKPInstance::readNumObjects(std::ifstream& f)
{
    std::string line;
    int numObjs;

    std::getline(f, line);

    numObjs = atoi(line.c_str());
    _numObjs = numObjs;
}

void MQKPInstance::allocateVariables()
{
    _weights = new int[getNumObjs()];

    _profits = new int*[getNumObjs()];
    for (auto i = 0; i < getNumObjs(); ++i) {
        _profits[i] = new int[getNumObjs()];
    }

    _capacities = new double[_numKnapsacks + 1];
}

void MQKPInstance::fillProfits(std::ifstream& f)
{
    std::string line;

    std::getline(f, line);

    int startIndex = line.find_first_not_of(' ');
    int endIndex = line.find(' ', startIndex);

    for (auto i = 0; i < getNumObjs(); ++i) {
        _profits[i][i] = atoi(line.substr(startIndex, endIndex - startIndex).c_str());

        startIndex = line.find_first_not_of(' ', endIndex);
        endIndex = line.find(' ', startIndex);
    }

    for (auto i = 0; i < getNumObjs() - 1; ++i) {
        std::getline(f, line);
        startIndex = line.find_first_not_of(' ');
        endIndex = line.find(' ', startIndex);

        for (auto j = i + 1; j < getNumObjs(); ++j) {
            _profits[i][j] = atoi(line.substr(startIndex, endIndex - startIndex).c_str());

            //The matrix is symetric
            _profits[j][i] = _profits[i][j];

            startIndex = line.find_first_not_of(' ', endIndex);
            endIndex = line.find(' ', startIndex);
        }
    }
}

void MQKPInstance::fillWeights(std::ifstream& f)
{
    std::string line;

    std::getline(f, line);

    int startIndex = line.find_first_not_of(' ');
    int endIndex = line.find(' ', startIndex);

    for (auto i = 0; i < getNumObjs(); ++i) {
        _weights[i] = atoi(line.substr(startIndex, endIndex - startIndex).c_str());

        startIndex = line.find_first_not_of(' ', endIndex);
        endIndex = line.find(' ', startIndex);
    }
}

void MQKPInstance::fillCapacities()
{
    int totalWeight = 0;
    for (auto i = 0; i < getNumObjs(); ++i) {
        totalWeight += _weights[i];
    }
    double capacity = totalWeight * .8 / _numKnapsacks;

    for (int i = 1; i < _numKnapsacks + 1; ++i)
        _capacities[i] = capacity;
}

void MQKPInstance::readInstance(char* filename, int numKnapsacks)
{

    /*
    * DONE Complete this function:
    *   1. read the number of objects
    *   2. allocate matrix and vector memory
    *   3. read profits and object weights, according to what has been previously discussed
    *   4. Obtain the capacities of the knapsacks:
    *      . Sum all the object weights
    *      . Multiply by 0.8
    *      . Divide the previous results by the number of knapsacks. This will be the capacity of each knapsack
    */

    _numKnapsacks = numKnapsacks;

    std::ifstream f(filename, std::ios::in);
    if (!f.is_open())
        exit(1);
    std::string line;

    std::getline(f, line); //Ignoring the name

    //Getting number of objects
    readNumObjects(f);

    //Allocating memory
    allocateVariables();

    //Filling profit matrix
    fillProfits(f);

    //Discard 3 lines
    std::getline(f, line); //Whiteline
    std::getline(f, line); // "0"
    std::getline(f, line); //Discarded value

    //Filling weight vector
    fillWeights(f);

    f.close();

    fillCapacities();
}
