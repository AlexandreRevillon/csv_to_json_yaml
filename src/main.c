/**
 * @brief      This file initializes arrays and sort them using 3 different algorithms
 *
 * @author     Jeremie
 * @date       2020
 */
#include <memory.h>
#include <sort_algorithms.h>
#include <stdbool.h>
#include <stdio.h>
#include <utils.h>

/**
 * @brief      Compares 3 arrays of integers
 *
 * @param      t1    1st array
 * @param      t2    2nd array
 * @param      t3    3rd array
 * @param[in]  N     the first N cells will to be checked
 *
 * @return     { description_of_the_return_value }
 */
bool compare_tab (int t1[], int t2[], int t3[], unsigned int N)
{
    for (unsigned int i = 0; i < N; i++)
    {
        if ((t1[i] != t2[i]) || (t2[i] != t3[i])) return false;
    }
    return true;
}



int main ()
{
    return 0;
}
