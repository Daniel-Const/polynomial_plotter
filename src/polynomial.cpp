/**
 * Recover a polynomial from a set of points
 */
#include <unordered_map>
#include <iostream>
#include <math.h>
#include "polynomial.hpp"
#include "point.hpp"

Polynomial::Polynomial(std::unordered_map<int, float> _terms)
{
    terms = _terms;
}

void Polynomial::print()
{

    std::cout << "P(x) = ";

    for (std::unordered_map<int, float>::iterator iter = terms.begin(); iter != terms.end(); ++iter)
    {
        if (iter != terms.begin())
        {
            std::cout << " + ";
        }
        std::cout << iter->second << "*x^" << iter->first;
    };
    std::cout << std::endl;
}

float Polynomial::evaluate(float value)
{
    float sum = 0;
    for (std::unordered_map<int, float>::iterator iter = terms.begin(); iter != terms.end(); ++iter)
    {
        sum += iter->second * pow(value, iter->first);
    };

    return sum;
}

bool Polynomial::containsPoint(Point point)
{
    /* Determine whether a point exists on the polynomial
     *
     * Given (x, y) determine if P(x) = y
     */

    return this->evaluate(point.x) == point.y;
}