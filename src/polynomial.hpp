#include <unordered_map>
#include "point.hpp"

class Polynomial
{

public:
    std::unordered_map<int, float> terms;
    Polynomial(std::unordered_map<int, float> _terms);
    float evaluate(float value);
    bool containsPoint(Point point);
    void print();
};