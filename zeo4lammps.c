#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define charsize   500
#define density    6
#define dimension  3
//this is a programme that import data of the target xml file and cut the polymr solution part to calculate its porosity 

int main (int argc, char *argv[])
{
	long double x, y, z;
		double vfractionP,xmin,xmax;
	int   ip,ip2,sizex,sizey,sizex1,sizez,list;
	int   i,j,iy, Nparticle, Nparticle1, Nparticle2, Npolymer, Nsolvent;
	double *position, *position2;
	int  time_step,f,filesize,file_gen;
	char flag, end;
	char line1[charsize],line2[charsize],line3[charsize];
	char line4[charsize],line5[charsize],line6[charsize];
	char line7[charsize],line8[charsize],line9[charsize];
	char line10[charsize],line11[charsize],line12[charsize];
	char line13[charsize],line13_2[charsize],line14[charsize];
	char file[charsize],file_name2[charsize],file_namenew[charsize],file_namegen[charsize];
	char         c;


	
	FILE *fp1, *fp3;
	strcpy(file, argv[1]);
	sizex = atoi(argv[2]);
	sizex1 = atoi(argv[3]);
	sizey = atoi(argv[4]);
	sizez = atoi(argv[5]);
	vfractionP = atof(argv[6]);
	xmin = atof(argv[7]);
	xmax = atoi(argv[8]);
	list = atoi(argv[9]);
	Nparticle = density * sizex * sizey * sizez;
	Nparticle1 = density * sizey * (sizex - sizex1) * sizez;
	Nparticle2 = density * sizey * sizex1 * sizez;
	Npolymer = vfractionP * Nparticle2;
	printf("file = %s   xmin = %f   xmax = %f\n", file, xmin, xmax);
	printf("Npolymer = %d     Nparticle = %d\n", Npolymer, Nparticle);
	printf("Nparticle1 = %d Nparticle2 = %d\n", Nparticle1, Nparticle2);

	//open the file,file 1 is the initial configuation,
	//create the corresponding arrays
		position = (double*)malloc(Nparticle*3*sizeof(double));
	if (position == NULL)
	{
		puts("memory allocation position failed. Goodbye!");
		exit(EXIT_FAILURE);
	} else
	{
	    memset(position,0,Nparticle*3*sizeof(double));  //initialization to be zero
	}

	//generate the new position array;
	position2 = (double*)malloc(Nparticle*3*sizeof(double));
	if (position == NULL)
	{
		puts("memory allocation position2 failed. Goodbye!");
		exit(EXIT_FAILURE);
	}else
	{
	    memset(position,0,Nparticle*3*sizeof(double));
	}



	if ((fp1 = fopen(file, "r+"))==NULL)
	{
		printf("CANNOT OPEN file 1\n");
		exit(0);
	}

  
	sprintf(file_namegen,"%03d.v1",list);
	printf("file_namegen = %s\n",file_namegen);

	if ((fp3 = fopen(file_namegen, "w+"))==NULL)
	{
	     printf("CANNOT OPEN file gen\n");
	     exit(0);
	}

	printf("file gen\n");

	// generate the position arrey;

	// jump the five head lines of file 1 and file 2
	fgets(line1,charsize,fp1);
	printf("%s",line1);
	fgets(line2,charsize,fp1);
	printf("%s",line2);
	fgets(line3,charsize,fp1);
	printf("%s",line3);
	fgets(line4,charsize,fp1);
	printf("%s",line4);
	fgets(line5,charsize,fp1);
	printf("%s",line5);
	fgets(line5,charsize,fp1);
	printf("%s",line5);
	fgets(line5,charsize,fp1);
	printf("%s",line5);
	fgets(line5,charsize,fp1);
	printf("%s",line5);
	fgets(line5,charsize,fp1);
	printf("%s",line5);
////read the position array
//
	 for (i=0;i<(Nparticle);i++)
	 {
	     ip = i*dimension;
	     fscanf(fp1, "%Lf %Lf %Lf", &x, &y, &z);

	     position[ip]   = 2*x;
	     position[ip+1] = 2*y;
	     position[ip+2] = 2*z;
	}

	printf("lucky success reading particle position\n");

	 j = 0;   //array 2 index
	 for (i=0;i<=(Npolymer-1);i++)  //i array 1 index
     {
	     ip   = i*dimension;
	     if ((position[ip]) - (2*xmin) > 0 )
	     {
	         if (((position[ip]) < (2 * xmax)))
	         {
	             ip2 = j * dimension;
	             position2[ip2] = position[ip];
	             position2[ip2 + 1] = position[ip + 1];
	             position2[ip2 + 2] = position[ip + 2];
	             j=j+1;
		     }

	     }
	 }
	 printf("total kept = %d\n",j);


	 fprintf(fp3,"Unit cell vectors:\n");
	 fprintf(fp3,"va= %d 0 0\n",2*sizey);
	 fprintf(fp3,"vb= 0 %d 0\n",2*sizez);
	 fprintf(fp3,"vc= 0 0 %f\n",2*xmax-2*xmin);
	 fprintf(fp3,"%d\n",j);

	for (i=0;i<=(j-1);i++)
	{ 
	    ip   =   i*dimension;
	    x    =   position2[ip];
	    y    =   position2[ip + 1];
	    z    =   position2[ip + 2];
	    fprintf(fp3, "H %15.10Lf  %15.10Lf  %15.10Lf \n", y,z,x);
	}

	fclose(fp3);
	fclose(fp1);
	//free memory
	free(position);
	free(position2);
return 0;
}

