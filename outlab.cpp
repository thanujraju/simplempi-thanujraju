#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>
#include <string> 
#include "data.hpp"
using namespace std;
void print_enemy(struct enemy e);  // for debug 
struct enemy get_enemy();  // get details of this enemy

int main(int argc, char *argv[]) {
  int rank;
  int size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  srand(0);
  int num_enemy = atoi(argv[1]);  
  struct enemy e[num_enemy];
  MPI_Datatype custom_type = get_custom_type(num_enemy);

  if (rank == 0) {
    for (int g = 0; g < num_enemy; g++) {
      e[g] = get_enemy();
#ifdef DEBUG  
  // cout<<"lol";    
      print_enemy(e[g]);
#endif
    }
    // cout<<std::to_string(custom_type)<<endl;
   MPI_Send(&e, 1, custom_type, 1, 0, MPI_COMM_WORLD);
  }
  if (rank == 1) {
    MPI_Recv(&e, 1, custom_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for (int g = 0; g < num_enemy; g++) {
      print_enemy(e[g]);
    }
  }
  MPI_Finalize();
  return 0;

}

void print_enemy(struct enemy e) {
     //cout << "Count: " << e.count << endl;
  // cout<<"lkjljls";
     for (int i = 0; i < e.count; i++) {
	  cout << "Loc " << i << ' ';
	  for (int j = 0; j < 3; j++) {
	       cout << e.location[i][j] << ' ';
	  }

	  cout << " Type " << e.type[i] << endl;
     }
     cout << "Experience: " << e.experience << endl;
     cout << "Strength: " << e.strength << endl;
     cout << "Supplies: " << e.supplies << endl;
     cout << "Fuel: " << e.fuel << endl;
     cout << "Stance:" << e.stance << endl;

}

struct enemy get_enemy() {
  struct enemy e;
  int count = (rand() % 20) + 1;
  e.count = count;
  int k;
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < 3; j++) {
      e.location[i][j] = rand() % 1000;
    }
    k = rand() % 5;
    e.type[i] = 'a' + k;
  }
  e.experience = rand() % 20;
  e.strength = rand() % 100;
  e.supplies = rand() % 100;
  e.fuel = rand() % 10000;
  e.stance = rand() % 11;
  return e;
}
