#include <vector>
#include <random>
#include<functional>
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

/*
  Initialize random number generators.
  Later on we can call uniform_dist() and it will return a uniform random number between 0 and 1.
*/
default_random_engine generator;
uniform_real_distribution<double> uniform_dist(0.0,1.0);
auto random_real = bind(uniform_dist, generator);

void print_desk(vector<vector<int>> desk, int timestep);

int main() {

  //parameters to control the simulation
  int length = 100;          //desk length
  int width = 100;           //desk width
  int time = 50000;            //number of time steps to run the simulation
  int deposit_rate = 100;     //number of time steps between deposit of each dust particle
  double Teffective = 100.0;    //constant controlling how often dust particles move due to "Brownian motion"
  double attraction = 1000;  //constant controlling the strength of the attraction between the dust and the desk

  //Create a 2d lattice to serve as a desk.  Each point of the lattice 
  vector<vector<int>> desk;
  //Populate the desk with one piece of dust on every lattice site
  vector<int> v(width, 1);
  for(int i = 0; i < length; i++) {
    desk.push_back(v);
  }

  //Create a file to collect data throughout the simulation
  ofstream output("avg_dust_height.dat");

  //Cycles through each time step
  double acceptance = 0;
  int chances = 0;
  for(int t = 0; t < time; t++) {

    double average_dust_height = 0.0;

    //Iterates through every lattice site on the desk
    for(int i = 0; i < length; i++) {
      for(int j = 0; j < width; j++) {

        //Deposits dust on desk
        if((t % deposit_rate) == 0) {
          desk[i][j]++;
        }

        //Move the particles of dust according to Brownian motion
        
        //Pick a random direction to go in
        if(desk[i][j] >= 1) {
          chances++;
          double rand = random_real();
          int newi = i;
          int newj = j;
          bool onboard = true; 
          if((0 <= rand) && (rand < 0.25) && (i+1 < length)) {
            newi++;
          } else if((0.25 <= rand) && (rand < 0.5) && (j+1 < width)) {
            newj++;
          } else if((0.5 <= rand) && (rand < 0.75) && (i-1 >= 0)) {
            newi--;
          } else if((0.75 <= rand) && (rand < 1.0) && (j-1 >= 0)) {
            newj--;
          } else {
            onboard = false;
          }
          //Compute the change in height of the dust piles
          int newheight = 0;
          if(onboard) {
            newheight = desk[newi][newj];
          } else {
            newheight = 0;
          }

          double probability = exp((-1.0/Teffective)*((newheight - attraction/(newheight + 1)) - (desk[i][j] - attraction/(desk[i][j] + 1))));

          if(probability > random_real()) {
            acceptance++;
            //remove dust particle from this lattice site
            desk[i][j]--;
            //move dust particle to an adjacent lattice site
            if(onboard) {
              desk[newi][newj]++;
            }
          }
        }
        

        //Adds the amount of dust at this lattice site to a running total
        average_dust_height += desk[i][j];
      }
    }

    //Calculates the average amount of dust over each lattice site
    if(t % 100) {
      average_dust_height = average_dust_height / (length * width);
      output << t << " " << average_dust_height << endl;
    }
    
    if(t == (time - 1)) {
      print_desk(desk, t);
    }
  }
  cerr << "Acceptance probability is " << acceptance/chances << endl;

}

void print_desk(vector<vector<int>> desk, int timestep) {
  ofstream output("desk_state_" + to_string(timestep) + ".dat");
  for(vector<int> v : desk) {
    for(int i : v) {
      output << i << " ";
    }
    output << endl;
  }
}