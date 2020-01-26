#include <vector>
#include <random>

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
  for(int i = 0; i < length; i++) {
    for(int j = 0; j < width; j++) {
      desk[i][j] = 1;
    }
  }

  //Cycles through each time step
  for(int t = 0; t < time; t++) {

    //Iterates through every lattice site on the desk
    for(int i =0; i < length; i++) {
      for(int j = 0; j < width; j++) {

        

      }
    }

  }

}