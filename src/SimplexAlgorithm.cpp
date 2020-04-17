//
// Created by CubeSky on 4/17/2020.
//

#include "SimplexAlgorithm.h"


vector<double> SimplexAlgorithm::simplex() {
    if (initialise_simplex() == -1)
    {
        return vector<double>(n + m, -2);
    }

    int code;

    while (!(code = iterate_simplex()));

    if (code == -1) return vector<double>(n + m, -1);

    vector<double> ret;
    ret.resize(n + m);
    for (int j=0;j<n;j++)
    {
        ret[N[j]] = 0;
    }
    for (int i=0;i<m;i++)
    {
        ret[B[i]] = b[i];
    }


    vector<double> res = vector<double>(ret.begin(), ret.begin() + n);
    return res;}

int SimplexAlgorithm::initialise_simplex() {
    int k = -1;
    double min_b = -1;
    for (int i=0;i<m;i++)
    {
        if (k == -1 || b[i] < min_b)
        {
            k = i;
            min_b = b[i];
        }
    }

    if (b[k] >= 0) // basic solution feasible!
    {
        for (int j=0;j<n;j++) N[j] = j;
        for (int i=0;i<m;i++) B[i] = n + i;
        return 0;
    }

    // generate auxiliary LP
    n++;
    for (int j=0;j<n;j++) N[j] = j;
    for (int i=0;i<m;i++) B[i] = n + i;

    // store the objective function
    double c_old[MAX_N];
    for (int j=0;j<n-1;j++) c_old[j] = c[j];
    double v_old = v;

    // aux. objective function
    c[n-1] = -1;
    for (int j=0;j<n-1;j++) c[j] = 0;
    v = 0;
    // aux. coefficients
    for (int i=0;i<m;i++) A[i][n-1] = 1;

    // perform initial pivot
    pivot(k, n - 1);

    // now solve aux. LP
    int code;
    while (!(code = iterate_simplex()));

    assert(code == 1); // aux. LP cannot be unbounded!!!

    if (v != 0) return -1; // infeasible!

    int z_basic = -1;
    for (int i=0;i<m;i++)
    {
        if (B[i] == n - 1)
        {
            z_basic = i;
            break;
        }
    }

    // if x_n basic, perform one degenerate pivot to make it nonbasic
    if (z_basic != -1) pivot(z_basic, n - 1);

    int z_nonbasic = -1;
    for (int j=0;j<n;j++)
    {
        if (N[j] == n - 1)
        {
            z_nonbasic = j;
            break;
        }
    }
    assert(z_nonbasic != -1);

    for (int i=0;i<m;i++)
    {
        A[i][z_nonbasic] = A[i][n-1];
    }
    swap(N[z_nonbasic], N[n - 1]);

    n--;
    for (int j=0;j<n;j++) if (N[j] > n) N[j]--;
    for (int i=0;i<m;i++) if (B[i] > n) B[i]--;

    for (int j=0;j<n;j++) c[j] = 0;
    v = v_old;

    for (int j=0;j<n;j++)
    {
        bool ok = false;
        for (int jj=0;jj<n;jj++)
        {
            if (j == N[jj])
            {
                c[jj] += c_old[j];
                ok = true;
                break;
            }
        }
        if (ok) continue;
        for (int i=0;i<m;i++)
        {
            if (j == B[i])
            {
                for (int jj=0;jj<n;jj++)
                {
                    c[jj] += c_old[j] * A[i][jj];
                }
                v += c_old[j] * b[i];
                break;
            }
        }
    }

    return 0;
}

int SimplexAlgorithm::iterate_simplex() {
    printf("--------------------\n");
    printf("State:\n");
    printf("Maximise: ");
    for (int j=0;j<n;j++) printf("%lfx_%d + ", c[j], N[j]);
    printf("%lf\n", v);
    printf("Subject to:\n");
    for (int i=0;i<m;i++)
    {
        for (int j=0;j<n;j++) printf("%lfx_%d + ", A[i][j], N[j]);
        printf("%lf = x_%d\n", b[i], B[i]);
    }

    // getchar(); // uncomment this for debugging purposes!

    int ind = -1, best_var = -1;
    for (int j=0;j<n;j++)
    {
        if (c[j] > 0)
        {
            if (best_var == -1 || N[j] < ind)
            {
                ind = N[j];
                best_var = j;
            }
        }
    }
    if (ind == -1) return 1;

    double max_constr = INFINITY;
    int best_constr = -1;
    for (int i=0;i<m;i++)
    {
        if (A[i][best_var] < 0)
        {
            double curr_constr = -b[i] / A[i][best_var];
            if (curr_constr < max_constr)
            {
                max_constr = curr_constr;
                best_constr = i;
            }
        }
    }
    if (isinf(max_constr)) return -1;
    else pivot(best_constr, best_var);

    return 0;
}

void SimplexAlgorithm::pivot(int x, int y) {
    printf("Pivoting variable %d around constraint %d.\n", y, x);

    // first rearrange the x-th row
    for (int j=0;j<n;j++)
    {
        if (j != y)
        {
            A[x][j] /= -A[x][y];
        }
    }
    b[x] /= -A[x][y];
    A[x][y] = 1.0 / A[x][y];

    // now rearrange the other rows
    for (int i=0;i<m;i++)
    {
        if (i != x)
        {
            for (int j=0;j<n;j++)
            {
                if (j != y)
                {
                    A[i][j] += A[i][y] * A[x][j];
                }
            }
            b[i] += A[i][y] * b[x];
            A[i][y] *= A[x][y];
        }
    }

    // now rearrange the objective function
    for (int j=0;j<n;j++)
    {
        if (j != y)
        {
            c[j] += c[y] * A[x][j];
        }
    }
    v += c[y] * b[x];
    c[y] *= A[x][y];

    // finally, swap the basic & nonbasic variable
    swap(B[x], N[y]);

}

SimplexAlgorithm::SimplexAlgorithm() {

}

void SimplexAlgorithm::generateData(vector<__float128> minUtil,vector<__float128> currUtil) {

    m=3;
    n= minUtil.size();
    b[0] = 1; b[1] = -1; b[2] = 0;
    for(int i = 0; i < minUtil.size(); i++){
        A[0][i] = -1;
        A[1][i] = 1;
        A[2][i] = minUtil[i];
        c[i] = currUtil[i];
    }
    v = 0;
}
