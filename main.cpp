// Github Link: https://github.com/garrettbearss/Banker-s-Algorithm/edit/main/main.cpp
// Author: Garrett Bearss
// Date: 4/19/2022
// main.cpp
// To run use gcc main.cpp -lstdc++
// then ./a.out
#include<iostream>
using namespace std;
  
// Keeps track of the number of processes
const int numP = 5;
  
// Keeps track of the number of resources
const int numR = 3;
  
// Function to find the needed resources of each process
void calculateNeededResource(int needed[numP][numR], int maxR[numP][numR], int allotted[numP][numR])
{
  // Calculates the needed resources of each process
  for(int i = 0 ; i < numP ; i++)
  {
    for(int j = 0 ; j < numR ; j++)
    {
      // Needed resource = max resource - allocated resource
      needed[i][j] = maxR[i][j] - allotted[i][j];
    }
  }
}

// Function to find out if the system is in safe state or not
bool checkSafeState(int processes[], int available[], int maxR[][numR], int allotted[][numR])
{
  int needed[numP][numR];
  
  // Function to calculate needed resources
  calculateNeededResource(needed, maxR, allotted);
  
  // Keeps track of which processes have finished
  bool finished[numP] = {0};
  
  // Stores the safe sequence
  int safeSequence[numP];
  
  // Make a copy of available resources
  int copyR[numR];
  for (int i = 0; i < numR ; i++)
  {
    copyR[i] = available[i];
  }
  
  // While all processes have not finished or the system is not in the safe state.
  int count = 0;
  while(count < numP)
  {
    // Finds a process which is not finished yet and whose needed resources can be satisfied with current copied resources.
    bool truth = false;
    for(int p = 0; p < numP; p++)
    {
      // Checks to see if a process is finished, if not then it continues
      if(finished[p] == 0)
      {
        // Checks if for all resources of the current process, if needed resources is less than copy
        int j;
        for(j = 0; j < numR; j++)
        {
          if(needed[p][j] > copyR[j])
          {
            break;
          }
        }
        // If all needs of the process were satisfied.
        if(j == numR)
        {
          // Add the allocated resources of current process to the available resources and free the resources afterward
          for(int k = 0 ; k < numR ; k++)
          {
            copyR[k] += allotted[p][k];
          }
          // Add this process to safe sequence.
          safeSequence[count++] = p;
  
          // Mark the current process as finished
          finished[p] = 1;
          truth = true;
        }
      }
    }
    // If we could not find a next process in safe sequence.
    if(truth == false)
    {
      cout << "System is not in safe state";
      return false;
    }
  }
  // If system is in safe state then safe sequence will be as below
  cout << "System is in safe state.\nSafe"
         " sequence is: ";
  for(int i = 0; i < numP ; i++)
  {
    cout << safeSequence[i] << " ";
  }
  return true;
}

// Main code
int main()
{
  // Number of processes
  int processes[] = {0, 1, 2, 3, 4};
  
  // Available instances of resources
  int available[] = {3, 3, 2};
  
  // Max resources that can be allocated to each process
  int maxR[][numR] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
  
  // Resources allocated to processes
  int allocated[][numR] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
  
  // Check to see if system is in a safe state or not
  checkSafeState(processes, available, maxR, allocated);
  
  return 0;
}
