/**
 * MQKPInstance.h
 * 
 * File defining the class MQKPInstance.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPINSTANCE_H__
#define __MQKPINSTANCE_H__

#ifndef __MQKPSOLUTION_H__
#include "MQKPSolution.h"
#else
class MQKPSolution;
#endif

#include <fstream>
#include <stdlib.h>
#include <time.h>
/**
 * Class for storing the information of an instance of the problem MQKP
 */
class MQKPInstance {
protected:
    /* DONE Define the properties of the class:
	 * _numKnapsacks Integer with number of knapsacks to consider. This is not read from the file, but established by the user.
	 * _numObjs Integer with the number of objects of the problem.
	 * _profits Matrix where the profits of the objects are stored. YOU HAVE TO ALLOCATE ITS MEMORY.
	 * _weights Vector with the weights of the objects. YOU HAVE TO ALLOCATE ITS MEMORY.
	 * _capacities Vector with the capacities of the knapsacks. YOU HAVE TO ALLOCATE ITS MEMORY. To avoid problems, store the vector
	 *             for (1 + numKnapsacks) elements and use the indices from index 1
	 */
    int _numKnapsacks, _numObjs, **_profits, *_weights;
    double* _capacities;

    void readNumObjects(std::ifstream&f), allocateVariables(), fillProfits(std::ifstream&f), fillWeights(std::ifstream&f), fillCapacities();

public:
    /**
	 * Default constructor
	 */
    MQKPInstance();

    /**
	 * Destructor
	 */
    ~MQKPInstance();

    /**
	 * Function for reading an input file.
	 * @param[in] filename Name of the file where the data of the instance can be found.
	 * @param[in] numKnapsacks Integer with the number of knapsacks to be considered. This is not read from the file,
	 *                         but established by the user.
	 */
    void readInstance(char* filename, int numKnapsacks);

    //Declare the methods (and define them in MQKPInstance.cpp) returning the information about the instance
    // of the problem. Among others, getNumObjs() and getNumKnapsacks()

    /**
	 * Function that returns the number of knapsacks in the problem
	 * @return Number of knapsacks
	 */
    inline int getNumKnapsacks() const { return _numKnapsacks; }

    /**
	 * Function that returns the total number of objects in the problem
	 * @return Number of objects
	 */
    inline int getNumObjs() const { return _numObjs; }

    /**
	 * Function that returns the matrix of the profits of each object pair
	 * @return Matrix of numObjects x numObjects with the profits
	 */
    inline int** getProfits() const { return _profits; }

    /**
	 * Function that returns the vector of the weight of each object
	 * @return Vector of numObjects with the weights
	 */
    inline int* getWeights() const { return _weights; }

    /**
	 * Function that returns the vector of the capacity of each knapsack
	 * @return Vector of numKnapsacks+1 with the capacities
	 */
    inline double* getCapacities() const { return _capacities; }

    /**
	 * Function returning how much the capacity constraint is is violated for the most over-weighted knapsack.
	 * @param[in] solution Reference to an object representing a solution to the problem.
	 * @return Maximum violation of the knapsack capacities.
	 */
    double getMaxCapacityViolation(MQKPSolution& solution);

    /**
	 * Function obtaining the sum of the individual and shared profits of the objects in the knapsacks.
	 * @param[in] solution Reference to an object representing a solution to the problem.
	 * @return Sum of the individual and shared profits of the objects in the knapsacks.
	 */
    double getSumProfits(MQKPSolution& solution);
};

#endif
