#include "./../headers/SmithWaterman.h"
#include <cstring>
#include <string>
#include <iostream>

double SmithWaterman::similarityScore(char a, char b) {

    if(a == b) {
        return 3;
    }

    return -3;
};


double SmithWaterman::findMax(const double array[]) {

    double max = array[0];

    for(int i = 1; i < 4; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
};


bool SmithWaterman::verifySequence(const std::string& sequenceFirst, const std::string& sequenceSecond, double threshold) {

    unsigned long lengthFirst = sequenceFirst.length();
    unsigned long lengthSecond = sequenceSecond.length();

    double **matrix = new double *[lengthFirst + 1];
    for (int i = 0; i < lengthFirst + 1; ++i) {
        matrix[i] = new double[lengthSecond + 1];
        std::memset(matrix[i], 0, sizeof(double) * (lengthSecond + 1));
    }

    double traceback[4];
    std::memset(static_cast<double*>(traceback), 0, sizeof(double)*4);

    for (unsigned i = 1; i <= lengthFirst; i++)
    {
        for(unsigned j = 1; j <= lengthSecond; j++)
        {
            traceback[0] = matrix[i-1][j-1] + SmithWaterman::similarityScore(sequenceFirst[i], sequenceSecond[j]);
            traceback[1] = matrix[i-1][j] - 2;
            traceback[2] = matrix[i][j-1] - 2;
            traceback[3] = 0;

            matrix[i][j] = SmithWaterman::findMax(static_cast<double*>(traceback));
        }
    }

    double matrixMax = 0;

    for(unsigned i = 1; i <= lengthFirst; i++) {
        for(unsigned j = 1; j <= lengthSecond; j++) {

            if(matrix[i][j] > matrixMax) {
                matrixMax = matrix[i][j];
            }
        }
    }

    for (int i = 0; i < lengthFirst + 1; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;


    unsigned long minLen = (lengthFirst > lengthSecond) ? lengthSecond : lengthFirst;

    return threshold < (matrixMax / minLen);

}