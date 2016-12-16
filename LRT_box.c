/*
Xibelly Eliseth Mosquera Escobar CC 1035428318

This code computes the LRT of a function in a 2D domain.

Steps
1) Create the medium -> a tophat function 
                  
                | 1 ; x,y (0,Lbox)
      f(x,y) =  |
                | 0 , elsewhere

 This medium is a rectangular box with size Lbox

2) Creates the rays 

- The rays denife the discretization, so: 

To generates the rays, the sources and detectors are located 2 times outside of the box, is to say at 2*Lbox

The rays are sampling with a rate of Delta_s = 2*Lbox / #rays 

Note: Parameters Lbox and # of rays are given by comand line

Our sources and detectors must rotate, i.e the rays, for that reason, the equation that are used to stablish their positions is:

      pos_sd_x =  j * sin(theta) + pos_x;   
      pos_sd_y = pos_y ;   

with 
     pos_x = ( i * Delta_s);
     pos_y = ( j * Delta_s);


3) Computes the LRT

The clasical RT consist in the line-integral, that is a sum along of the ray.

      Sum f(x_i,y_i)  -> with x_i, y_i are points that define the rays

 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include <time.h>

//Glocbal Variables
double Lbox, Lrays;
double Delta_s;
int Nrays;

FILE *out1 = NULL;
FILE *out2 = NULL;
FILE *out3 = NULL;

//Structures

struct data
{
  double x;
  double y;
  double fxy;
  
};
struct data *pos, *ray;

int main(int argc, char *argv[])
{
  int i,j;
  int Ncell;
  int Ntotalcells;
  int id_cell;  
  int id_ray;
  int angu;
  int Ntotalrays;
    
  double cell_size;
  double theta;
  double radon;

  double xmax;
  double ymax;
  
  double xmin;
  double ymin;
  
  char buff[200];
  
  //Carga de parametros

  Lbox = atoi(argv[1]);        //Longitud de la caja

  Nrays = atoi(argv[2]);   //# de particlas
  
  if(argc != 3)
    {
      printf("ERROR--> use as:\n");
      printf(" USE: %s  Lbox Nrays  \n",argv[0]);
      exit(0);
    }

  printf("%lf %d\n", Lbox, Nrays);

  if(Nrays < 0)
    printf("ERROR--> there are not rays");

  printf("BOX SIZE IS :%lf\n",Lbox);
  printf("THE NUMBER OF RAYS IS:%d\n",Nrays);

  
  Lrays = 2.0*Lbox;
  
  Delta_s =  (Lrays) / Nrays ;

  Ncell = 100;

  Ntotalcells = Ncell*Ncell;

  Ntotalrays = Nrays * Nrays;
  
  printf("THE RAY LENGHT IS:%lf\n",Lrays);
  printf("THE SAMPLE RATE OF THE RAYS IS: %lf\n",Delta_s);

  pos = malloc((size_t) Ntotalcells*sizeof(struct data));

  ray = malloc((size_t) Ntotalrays*sizeof(struct data));


  printf("STATE OF PARAMETERS LOADING IS: SUCCESSFUL\n");

  //-------------------------------------------------------------------Creating the Box and the tophat function

  sprintf(buff,"box.dat");
  out1 = fopen(buff,"w");

 
  cell_size = Lbox / (1.0 * Ncell);

  for(i=0; i<Ncell; i++)
    {

      for(j=0; j<Ncell; j++)
	{
	  id_cell = Ncell * i + j;

	  pos[id_cell].x = cell_size * 0.5 + i * cell_size;
	  pos[id_cell].y = cell_size * 0.5 + j * cell_size;

	  
	  pos[id_cell].fxy = 1.0; //tophat function

	  fprintf(out1,"%lf %lf %lf\n",pos[id_cell].x, pos[id_cell].y,pos[id_cell].fxy);
	  
	}

    }
  
  printf("THE BOX IS CREATED\n");

  //-------------------------------------------------------------------Locating the sources and the detectors-Creating the rays-

     
  for(angu=0; angu<=360; angu=angu+20)
    {
      sprintf(buff,"rays_theta%d.dat",angu);
      out2 = fopen(buff,"w");
       
      for(i=0; i<Nrays; i++)
	{
	   	   
	   for(j=0; j<Nrays; j++)
	     {
	       id_ray = Nrays * i + j ;
	       	       
	       theta = (angu * M_PI)/180.0;

	       ray[id_ray].x = (j * sin(theta)) + ( i * Delta_s) ;
	       
	       ray[id_ray].y =  (j * Delta_s) ;
	       
	       fprintf(out2,"%lf %lf %d\n",ray[id_ray].x,ray[id_ray].y, angu);
	       
	     }
	}
      
    }

  //-------------------------------------------------------------------Computing the RT

  
  sprintf(buff,"LRT.dat");
  out3 = fopen(buff,"w");
  
  
  for(angu=0; angu<=360; angu=angu+20)
    {
      for(j=0; j<Ntotalrays; j++)
	{
	  
	  for(i=0; i<Ntotalcells; i++)
	    {
	      xmin = ray[j].x;
	      xmax = ray[j+1].x;
	      
	      ymin = ray[j].y;
	      ymax = ray[j+1].y;
	      
	      if( ( pos[i].y >=ymin) && ( pos[i].y < ymax ) )
		{
		  radon +=  pos[i].fxy; 
		  fprintf(out3,"%lf %d\n",radon, angu);
		}
	      
	    }
	}
      
    }
 
  return 0;

}
