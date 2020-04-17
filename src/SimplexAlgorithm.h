//
// Created by CubeSky on 4/17/2020.
//

#ifndef EXERCISE_SIMPLEXALGORITHM_H
#define EXERCISE_SIMPLEXALGORITHM_H
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include<quadmath.h>

using namespace std;

#define MAX_N 1001
#define MAX_M 1001
class SimplexAlgorithm {
public:
    SimplexAlgorithm();
    vector<double> simplex();
    void generateData(vector<__float128> minUtil, vector<__float128>currUtil);
private:
    int n, m;
    double A[MAX_M][MAX_N], b[MAX_M], c[MAX_N], v;
    int N[MAX_N], B[MAX_M]; // nonbasic & basic
    inline int initialise_simplex();
    inline int iterate_simplex();
    inline void pivot(int x, int y);




};


#endif //EXERCISE_SIMPLEXALGORITHM_H
