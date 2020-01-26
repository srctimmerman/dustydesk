#include <vector>
#include <random>
#include<functional>
#include <iostream>
#include <fstream>

using namespace std;

/*
  Initialize random number generators.
  Later on we can call uniform_dist() and it will return a uniform random number between 0 and 1.
*/
default_random_engine generator;
uniform_real_distribution<double> uniform_dist(0.0,1.0);
auto random_real = bind(uniform_dist, generator);

int main() {

  //parameters to control the simulation
  int length = 20;          //desk length
  int width = 20;           //desk width
  int time = 50;            //number of time steps to run the simulation
  int deposit_rate = 3;     //number of time steps between deposit of each dust particle
  double brownian = 2.0;    //constant controlling how often dust particles move due to "Brownian motion"
  double attraction = 1.0;  //constant controlling the strength of the attraction between the dust and the desk

  //Create a 2d lattice to serve as a desk.  Each point of the lattice 
  vector<vector<int>> desk;
  //Populate the desk with one piece of dust on every lattice site
  vector<int> v(width, 1);
  for(int i = 0; i < length; i++) {
    desk.push_back(v);
  }

  cerr << "hi" << endl;

  //Create a file to collect data throughout the simulation
  ofstream output("average_dust_height.dat");

  //Cycles through each time step
  for(int t = 0; t < time; t++) {

    double average_dust_height = 0.0;

    //Iterates through every lattice site on the desk
    for(int i = 0; i < length; i++) {
      for(int j = 0; j < width; j++) {

        //Deposits dust on desk
        if((t % deposit_rate) == 0) {
          desk[i][j]++;
        }

        //Adds the amount of dust at this lattice site to a running total
        average_dust_height += desk[i][j];
      }
    }

    //Calculates the average amount of dust over each lattice site
    average_dust_height = average_dust_height / (length * width);
    output << average_dust_height << endl;

  }
}