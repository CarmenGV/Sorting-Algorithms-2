#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	    return -1;
      else
	    return 1;
    }
} /*>>>*/

int digit_compare(char* s1, int s1_len, char* s2, int s2_len, int d)
{
    if((s1_len > d) && ((s2_len <= d) || (s1[d] > s2[d])))
    {
        return 1;
    } 
    else
    {
        return -1;
    }
    cout << endl;
}

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
      {
    	  A[i+1] = A[i];
    	  i = i - 1;
      }

      A[i+1] = key;
    }
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
    int i;
    char* key;
    int key_len;
    for(int j = l+1; j < r; j++)
    {
        key = A[j];
        key_len = A_len[j];
        i = j - 1;
        while ((i >= l) && (digit_compare(A[i], A_len[i], key, key_len, d) > 0))
        {
            A[i+1] = A[i];
            A_len[i+1] = A_len[i];
            i = i - 1;
        }
        A[i+1] = key;
        A_len[i+1] = key_len;
    }
}

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
    int C[123] = {0};
    for(int j = 0; j < n; j++)
    {
        if(A_len[j] <= d)
        {
            C[0]++;
        } else{
            C[A[j][d]]++;
        }
    }
    for(int k = 1; k <= 122; k++)
    {
        C[k] += C[k-1];
    }
    for(int j = n-1; j >= 0; j--)
    {
        if(A_len[j] <= d)
        {
            B[C[0] - 1] = A[j];
            B_len[C[0] - 1] = A_len[j];
            C[0]--;
        } else
        {
            B[C[A[j][d]] - 1] = A[j];
            B_len[C[A[j][d]] - 1] = A_len[j];
            C[A[j][d]]--;
        }
    }
    for(int i = 0; i < n; i++)
    {
        A[i] = B[i];
        A_len[i] = B_len[i];
    }
}

void radix_sort_is(char** A, int* A_len, int n, int m)
{ 
    for(int i = m; i >= 0; i--)
    {
        insertion_sort_digit(A, A_len, 0, n, i);
    }
}

void radix_sort_cs(char** A, int* A_len, int n, int m)
{ 
    char* B[n];
    int B_len[n];
    for(int i = m; i >= 0; i--)
    {
        counting_sort_digit(A, A_len, B, B_len, n, i);
    }
}



/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
