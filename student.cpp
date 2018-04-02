#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>
#include "data.hpp"
using namespace std;
void get_arr_type(MPI_Datatype &typeof_2d)
{
	int cols[20] ;
	int arr_2d[20];
	for(int i = 0 ; i < 20 ;i++)
	{
		cols[i] = 3;
	}
	MPI_Aint base;
	MPI_Address(arr_2d[0],&base);
	MPI_Aint displacements[20];
	for(int i = 0 ; i < 20 ;i++)
	{
		MPI_Address(arr_2d[i],&displacements[i]);
		displacements[i] -= base;
	}
	MPI_Type_hindexed(20,cols,displacements,MPI_INT,&typeof_2d);
	MPI_Type_commit(&typeof_2d);
}
MPI_Datatype get_custom_type(int num_enemy) {
	 MPI_Datatype retValue;
	 /*
	  *      Your Code Goes Here
	  */
	 /////////////
	 struct enemy ds;
	 MPI_Datatype typeof_2d;
	 get_arr_type(typeof_2d);
	 MPI_Datatype type[8] = &{MPI_INT, typeof_2d ,MPI_CHAR,MPI_DOUBLE,MPI_DOUBLE,MPI_INT,MPI_DOUBLE,MPI_INT};
	 int len[8] = {1,1,20,1,1,1,1,1};
	 MPI_Aint base;
		MPI_Address(ds,&base);
		MPI_Aint displacements[8];
		displacements[0] = &ds.count-base;
		displacements[1] = &ds.location-base;
		displacements[2] = &ds.type-base;
		displacements[3] = &ds.experience-base;
		displacements[4] = &ds.strength-base;
		displacements[5] = &ds.supplies-base;
		displacements[6] = &ds.fuel-base;
		displacements[7] = &ds.stance-base;
MPI_Type_create_struct(8,len,displacements,type,&retValue);
MPI_Type_commit(&retValue);



	 return retValue;
}

