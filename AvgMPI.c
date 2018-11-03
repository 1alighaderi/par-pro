/*
 ============================================================================
 Name        : AvgMPI.c
 Author      : Ali
 Version     :
 Copyright   : Keyboard AZAD :)
 Description : Calculate Pi in MPI
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>


const int MAX_STRING = 76;
#define COURSE_NUM 5
#define STUDENT_NUM 2
int main() {
	char list[MAX_STRING];
	int proc_num;
	int proc_id;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	if (proc_id != 0) {
		int mark[COURSE_NUM][2] = {
				{0, 16},{0, 19},{0, 14},{1, 19},{1, 15}};
			for (int i=0 ; i<COURSE_NUM ; i++)
			{
				sprintf(list ,"%d %d" ,mark[i][0] ,mark[i][1]);
				MPI_Send(list, strlen(list)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
		}
	else
	{
			for (int q = 1; q < proc_num ; q++) {
				int sum [STUDENT_NUM ] = {0};
				int count [STUDENT_NUM ] = {0};
					for(int t = 0 ; t < COURSE_NUM ; t++)
					{
						MPI_Recv(list, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						int grade,id ;
						sscanf(list ,"%d %d" ,&id ,&grade);
						sum[id]+=grade ;
						count[id]+=1 ;

					}
				for(int p = 0 ;p<STUDENT_NUM ; p++)
				{
					float average =((float) sum[p])/count[p] ;
					printf("average of student %d = %f \n" , p , average ) ;
				}
				}
				}
		MPI_Finalize();
		return 0;
	}
