/*
 * MQKPSolution.cpp
 *
 * File defining the methods of the class MQKPSolution.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPSolution.h"
#include "MQKPInstance.h"

MQKPSolution::MQKPSolution(MQKPInstance& instance)
{
    //DONE Complete initializing the properties. Initially, all the objects are out of any knapsack (=0)

    this->_numObjs = instance.getNumObjs();
    this->_fitness = 0;
    this->_sol = new int[_numObjs];

    for (auto i = 0; i < _numObjs; ++i)
        _sol[i] = 0;
}

MQKPSolution::~MQKPSolution()
{
    delete[] _sol;
    _numObjs = 0;
    _fitness = 0;
}

void MQKPSolution::putObjectIn(int object, int knapsack)
{
    _sol[object] = knapsack;
}

int MQKPSolution::whereIsObject(int object)
{
    return _sol[object];
}
