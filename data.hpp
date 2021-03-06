MPI_Datatype get_custom_type(int num_enemy);

struct enemy {
  int count;                    // num of units 1 to 20
  int location[20][3];          // location of units x,y,z
  char type[20];                // one of 'a,b,c,d,e'
  double experience;            // experience of enemy 0-20 yrs
  double strength;              // 0-100, 0 -> dead, 100-> full
  int supplies;                 // num of days
  double fuel;                  // obvious
  int stance;                   // 0-10, defensive to offensive
};

