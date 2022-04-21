// Github Link: https://github.com/garrettbearss/Banker-s-Algorithm/edit/main/main.cpp
// Author: Garrett Bearss
// Date: 4/21/2022
// main.cpp
// To run use the following commands:
// $ g++ main.cpp -o main
// ./main
#include<iostream>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

void getData(vector<vector<int>> &allocated, vector<vector<int>> &maxR, vector<int> &available, int &numP, int &numR)
{
  // Opens input file
  ifstream in;
  in.open("input.csv");

  // Checks to see if file faild to open
  if(!in) 
  {
    std::cerr << "File was unable to open..." << '\n';
    exit(1);
  }

  char c;
  int count = 0;
  string str;
  vector<int> row;

  // While you haven't reached the end of the file
  while(!in.eof()) 
  {
    // Reads in a character
    in.get(c);
    // Checks if the character is a letter
    if(!isdigit(c)) 
    { 
      // Checks to see if the letter is blank
      if(str != "") 
      {
        // Converts the letter to an int
        int num = stoi(str);
        if(count == 2) 
        {
          available.push_back(num);
        }        
        // Pushes the num value onto the row
        row.push_back(num);
      }
      // Resets the value of the input
      str = "";
    }
    // Adds the character to a string if it is a number
    else if(isdigit(c) && c != ' ' && c != ',') 
    {
      str.push_back(c);
    }
    // Checks to see if there is a new line character
    if(c == '\n' || c == '\t' || c == '\r') 
    {
      // Resets the count variable
      count = 0;
      // Clears row's values
      row.clear();            
    }
    // Checks for a comma
    else if(c == ',') 
    {
      // Checks if the rows input add to the allocated ones
      if(count == 0) 
      {
        allocated.push_back(row);
      }
      // Checks if the rows input add to the max resources
      else if(count == 1) 
      {
        maxR.push_back(row);
      }
      // Clears row's values
      row.clear();
      // Increments count
      count++;
    }
  }
  // Sets the number of processes based on allocated's size
  numP = allocated.size();
  // Sets the number of resources based on avaiable's size
  numR = available.size();
}

// Function to find out if the system is in safe state or not
void checkSafeState(vector<vector<int>> &allocated, vector<vector<int>> &maxR, vector<int> &available, int &numP, int &numR)
{
  // Holds the needed resources
  int needed[numP][numR];
  
  // Used calculate needed resources
  for(int i = 0 ; i < numP ; i++)
  {
    for(int j = 0 ; j < numR ; j++)
    {
      // Needed resource = max resource - allocated resource
      needed[i][j] = maxR[i][j] - allocated[i][j];
    }
  }
  
  // Keeps track of which processes have finished
  bool finished[numP];
  // Sets the finished array to 0
  for(int i = 0; i < numP; i++){
    finished[i] = 0;
  }
  
  // Stores the safe sequence
  int safeSequence[numP];

  // Acts as a count for traversing safeSequence
  int count = 0;

  // Iterates through all the processes
  for(int i = 0; i < numP; i++)
  { 
    // Iterates through all of the processes to allow for each possible senario
    for(int j = 0; j < numP; j++)
    {
      // If a proceess has not finished yet
      if(finished[j] == false)
      { 
        // Turns to true when able to add to safeSequence
        int truth = false;
        // Iterates through all the processes
        for(int k = 0; k < numR; k++)
        {
          // If not able to complete the process
          if(needed[j][k] > available[k])
          {
            truth = 1;
            break;
          }
        }
        // If a process was able to finish
        if(truth == false)
        {
          // Adds that process to the safe sequence
          safeSequence[count++] = j;
          // Iterates through all resources
          for(int l = 0; l < numR; l++){
            // Adds the allocated resources from that process to the available
            available[l] += allocated[j][l];
          }
            // Sets that process to finished
            finished[j] = true;
        }
      }
    }
  }
  // Keeps track of if system is in safe state
  int truth = true; 
  // Iterates through all processes
  for(int i = 0; i < numP; i++) 
  {
    // If process is unfinished
    if(finished[i] == 0)
    {
      truth = 0;
    }
  }
  // If unable to get a safe sequence
  if(truth == false)
  {
    cout << "System is not in safe state";
    return;
  }
  // If system is in a safe state
  if(truth == true)
  {
    cout << "Safe sequence is: \n";
    // Prints safe sequence
    for(int i = 0; i < numP - 1; i++){
      cout << safeSequence[i] << " "; 
    }
      cout << safeSequence[numP-1] << '\n';
    }
}

// Main code
int main()
{
  // Holds the number of processes
  int numP;
  // Holds the number of resources
  int numR; 
  // Holds the allocated resources
  vector<vector<int>> allocated;
  // Holds the max resources
  vector<vector<int>> maxR;
  // Holds the available resources
  vector<int> available;
  // Takes data from input at stores it
  getData(allocated, maxR, available, numP, numR);
  // Checks to see if system is in a safe state or not
  checkSafeState(allocated, maxR, available, numP, numR);
  return 0;
}
