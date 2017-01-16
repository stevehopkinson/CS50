/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1)
    {
        return false;
    }
    
    // TODO: implement a searching algorithm
    int min = 0, max = n - 1; 
    
    while (true)
    {
        int mid = (max + min) / 2;
        if (values[mid] == value)
        {
            return true;
        }
        else if (max == min)
        {
            return false;
        }
        else if (values[mid] < value)
        {
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    bool sorted = false;
    int temp;
    
    do
    {
        sorted = true;
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i+1])
            {
                temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                sorted = false;
            }
        }
    }
    while (!sorted);
    
    return;
}
