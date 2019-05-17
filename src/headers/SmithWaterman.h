#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include <string>


class SmithWaterman {

public:

    static bool verifySequence(const std::string& sequenceFirst, const std::string& sequenceSecond, double threshold);


private:

    static double similarityScore(char a, char b);
    static double findMax(const double array[]);

};

#endif
