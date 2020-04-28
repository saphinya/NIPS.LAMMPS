#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define xboxsize   160
#define yboxsize   100
#define zboxsize   100
#define xboxsize1  100
#define yboxsize1  100
#define zboxsize1  100
#define ndensity   3
#define vfraction  0.16
#define halfbox2   45.0000000
#define Nparticle1 3000000
#define Nparticle2 4800000
#define charsize     100
#define Average  1

int main (void)
{
//define arrays and variables
	double x,y,z;
	int   ip,ip2,xx,yy,zz,sum;
	int   i,j,q,k,iy,point,file;
	int   nparticles,ptype1,ptype2,ptype3,ptype;
	int  time_step,f,filesize,file_gen;
	char *type, *type2, flag, end;
	int   ***densityp, ***densitys, ***densityn, ***density, *nflag;
	double  ***density1,***density2,***density3,***density1total,***density2total,***density3total;
	char line1[charsize],line2[charsize],line3[charsize];
	char line4[charsize],line5[charsize],line6[charsize];
    char file_name1[charsize],file_name2[charsize],file_namenew[charsize],file_namegen[charsize];
    FILE *fp1,*fp2,*fp3; 

//open the original file,file 1 and file 2 are two initial configuations, while the third file is the aimed configuation.
//read the file one by one
			 nparticles=ndensity*xboxsize1*yboxsize1*zboxsize1;
			 ptype1 = nparticles*vfraction;         
		//polymer particle number when volume density is 15%ฃฌcan be changed
			 ptype2 = nparticles*(1-vfraction);  
		//solvent  particle numberฃฌcan be changed
			 ptype3 = ndensity*xboxsize1*(yboxsize-yboxsize1)*zboxsize1;
		// create arraye		     
			 ptype = ptype1 +ptype2 + ptype3;


	nflag = (int*)malloc(ptype*sizeof(int));
	if (nflag == NULL)
	{
		puts("memory allocation type failed. Goodbye!");
		exit(EXIT_FAILURE);
	}else
	{ memset(nflag,0,ptype*sizeof(int));  //initialization to be zero
	}

	densityp = (int***)malloc(xboxsize* sizeof(int**));  //polymer number density
		for(i=0; i< xboxsize; i++)   
		{     
		densityp[i] = (int**)malloc(yboxsize*sizeof(int*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 densityp[i][j] = (int*)malloc(zboxsize*sizeof(int));   
			}
		}

	densitys = (int***)malloc(xboxsize* sizeof(int**));  //solvent number density 
		for(i=0; i< xboxsize; i++)   
		{     
		densitys[i] = (int**)malloc(yboxsize*sizeof(int*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 densitys[i][j] = (int*)malloc(zboxsize*sizeof(int));   
			}
		}

	densityn = (int***)malloc(xboxsize* sizeof(int**));   //nonsolvent number density
		for(i=0; i< xboxsize; i++)   
		{     
		densityn[i] = (int**)malloc(yboxsize*sizeof(int*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 densityn[i][j] = (int*)malloc(zboxsize*sizeof(int));   
			}
		}

	density = (int***)malloc(xboxsize* sizeof(int**));   //density of all particles
			for(i=0; i< xboxsize; i++)   
			{     
			density[i] = (int**)malloc(yboxsize*sizeof(int*));   
				for(j=0; j< yboxsize; j++)   
				{   
					 density[i][j] = (int*)malloc(zboxsize*sizeof(int));   
				}
			}
	density1 = (double***)malloc(xboxsize* sizeof(double**));   
		for(i=0; i< xboxsize; i++)   
		{     
		density1[i] = (double**)malloc(yboxsize*sizeof(double*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 density1[i][j] = (double*)malloc(zboxsize*sizeof(double));   
			}
		}

	density2 = (double***)malloc(xboxsize* sizeof(double**));   
		for(i=0; i< xboxsize; i++)   
		{     
		density2[i] = (double**)malloc(yboxsize*sizeof(double*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 density2[i][j] = (double*)malloc(zboxsize*sizeof(double));   
			}
		}

	density3 = (double***)malloc(xboxsize* sizeof(double**));   
		for(i=0; i< xboxsize; i++)   
		{     
		density3[i] = (double**)malloc(yboxsize*sizeof(double*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 density3[i][j] = (double*)malloc(zboxsize*sizeof(double));   
			}
		}
	density1total = (double***)malloc(xboxsize* sizeof(double**));   
		for(i=0; i< xboxsize; i++)   
		{     
		density1total[i] = (double**)malloc(yboxsize*sizeof(double*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 density1total[i][j] = (double*)malloc(zboxsize*sizeof(double));   
			}
		}

	density2total = (double***)malloc(xboxsize* sizeof(double**));   
		for(i=0; i< xboxsize; i++)   
		{     
		density2total[i] = (double**)malloc(yboxsize*sizeof(double*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 density2total[i][j] = (double*)malloc(zboxsize*sizeof(double));   
			}
		}
	density3total = (double***)malloc(xboxsize* sizeof(double**));   
		for(i=0; i< xboxsize; i++)   
		{     
		density3total[i] = (double**)malloc(yboxsize*sizeof(double*));   
			for(j=0; j< yboxsize; j++)   
			{   
				 density3total[i][j] = (double*)malloc(zboxsize*sizeof(double));   
			}
		}


				for( i=0; i<xboxsize; i++){       //initilize the arrays
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							densityp[i][j][q] = 0;
							densitys[i][j][q] = 0;
							densityn[i][j][q] = 0;
							density[i][j][q]  = 0;
							
							density1[i][j][q] = 0.0;
							density2[i][j][q] = 0.0;
							density3[i][j][q] = 0.0;
						}
					}
				}
//open filelist file, read the file names
    file = 0;  //calculate the file number

		if ((fp1 = fopen("filelist", "r+"))==NULL)   //check if the file is okay
		{
			printf("CANNOT OPEN file 1\n");           
		exit(0);                               
		}
	   printf("file1\n");

	     file_gen  =   1 ;

while(!feof(fp1))   //judge if reach the file end
{	

	if (file==0)		//determine which loop should be adopted
	{
		   fscanf(fp1,"%s",file_name1); //read the file name
		   filesize  =  strlen(file_name1);
			for (i=0;i<=(filesize-2);i++)
			{
				file_namenew[i]=file_name1[i+2];
			} 
		   printf("new file name = %s, its size is %d\n" , file_namenew, strlen(file_namenew));

			 if ((fp2 = fopen(file_namenew, "r"))==NULL)    //open the target xml file
			{
			   printf("CANNOT OPEN the xml file\n");              
			exit(0);                               
			}

			
		   sprintf(file_namegen,"v.%d.vtk",file_gen); 
		   printf("file_namegen = %s\n",file_namegen); //generate the vtk file name

			if ((fp3 = fopen(file_namegen, "w+"))==NULL)   
		   {
			   printf("CANNOT OPEN file gen\n");             
			   exit(0);                               
			}
		
		//write the head lines of the vtk files
			fprintf(fp3,"# vtk DataFile Version 3.1\n");
			fprintf(fp3,"VTK file containing grid data\n");
			fprintf(fp3,"ASCII>\n"); fputc('\n',fp3);

			fprintf(fp3,"DATASET STRUCTURED_POINTS\n");
			fprintf(fp3,"DIMENSIONS   90   240   90\n");
			fprintf(fp3,"ORIGIN    0   0   0\n");
			fprintf(fp3,"SPACING   1   1   1\n"); fputc('\n',fp3);
		     
			fprintf(fp3,"POINT_DATA 1944000\n");
			fprintf(fp3,"SCALARS c float\n");
			fprintf(fp3,"LOOKUP_TABLE default\n");
			// generate the position and type arrey;
			// jump the five head lines of file 1 and file 2
			fgets(line1,charsize,fp2);
		//	printf("%s",line1);
			fgets(line2,charsize,fp2);
		//	printf("%s",line2);
			fgets(line3,charsize,fp2);
		//	printf("%s",line3);
			fgets(line4,charsize,fp2);
		//	printf("%s",line4);
			fgets(line5,charsize,fp2);
		//	printf("%s",line5);	

		//initialize the nflag 
			 for (i=1;i<= ptype;i++)
			{
				if (i<= ptype1) {
				  nflag[i-1] = 1;
				}else if (ptype1< i && i <= (ptype1+ptype2)) {
				  nflag[i-1] = 2; 
				}else if ((ptype1+ptype2)< i && i <= (ptype1+ptype2+ptype3)) {
				  nflag[i-1] = 3;
				}
				//fprintf(fp3,"%d  %d\n", i, nflag[i-1] );
			 }

	  // read the position data
			 xx = 0;
             yy = 0;
			 zz = 0;
 			 for (i=1;i<= (Nparticle2+Nparticle1);i++)
			{
			         //fprintf(fp3,"i = %d\n" ,i);
				fscanf(fp2, "%lf %lf %lf", &x, &y, &z);
				 if (x < 0) xx =  ceil(x) +  xboxsize*0.5;
				 else xx  = floor(x)+ xboxsize*0.5;
				 if (y < 0) yy =  ceil(y) +  yboxsize*0.5;
				 else yy = floor(y)+ yboxsize*0.5;
				 if (z < 0) zz =ceil(z) + zboxsize*0.5;
				 else zz =floor(z) + zboxsize*0.5;
				 if (xx > xboxsize)  xx = xboxsize;
				 else if (xx < 1 )       xx = 1;
				 if (yy > yboxsize)  yy = yboxsize;
				 else if (yy < 1 )        yy = 1;
				 if (zz > zboxsize)  zz = zboxsize;
				 else if (zz < 1 )       zz = 1;
				 if (i <= (Nparticle2+Nparticle1))
				 {
					 if (nflag[i-1] == 1)      densityp[xx-1][yy-1][zz-1] = densityp[xx-1][yy-1][zz-1]+1;
					 else if (nflag[i-1] == 2) densitys[xx-1][yy-1][zz-1] = densitys[xx-1][yy-1][zz-1]+1;
					 else if (nflag[i-1] == 3) densityn[xx-1][yy-1][zz-1] = densityn[xx-1][yy-1][zz-1]+1;

				 }

			}

				for( i=0; i<xboxsize; i++){
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							density[i][j][q] = densityp[i][j][q] + densitys[i][j][q] + densityn[i][j][q];
						}
					}
				}
				for( i=0; i<xboxsize; i++){
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							if (density[i][j][q]!=0)
							{
							density1[i][j][q] = (double)densityp[i][j][q]/(double)density[i][j][q];
							density2[i][j][q] = (double)densityn[i][j][q]/(double)density[i][j][q];
							density3[i][j][q] = (double)densitys[i][j][q]/(double)density[i][j][q];
							}
							else 
							{
							density1[i][j][q] = 0.0;
							density2[i][j][q] = 0.0;
							density3[i][j][q] = 0.0;
							}
						}
					}
				}
              point = 0;
				for( q=0; q<zboxsize; q++){
					for( j=0; j<yboxsize; j++){
						for( i=0; i<xboxsize; i++){
							fprintf(fp3, "%f\n", density1[i][j][q]);
							point = point + 1;
						}
					}
				}
              printf("point = %d  \n", point);
				for( i=0; i<xboxsize; i++){       //initilize the arrays
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							densityp[i][j][q]      = 0;
							densitys[i][j][q]      = 0;
							densityn[i][j][q]      = 0;
							density[i][j][q]       = 0;
							
							density1[i][j][q]      = 0.0;
							density2[i][j][q]      = 0.0;
							density3[i][j][q]      = 0.0;
							density1total[i][j][q] = 0.0;
							density2total[i][j][q] = 0.0;
							density3total[i][j][q] = 0.0;
						}
					}
				}

			   fclose(fp2);fclose(fp3);
				   file_gen  =   file_gen + 1;
				   file      =   file     + 1;
                                   printf ("file = %d",file);
	}
	else if ((file % Average) != 0)
	 {
		   fscanf(fp1,"%s",file_name1); //read the file name
		   filesize  =  strlen(file_name1);
			for (i=0;i<=(filesize-2);i++)
			{
				file_namenew[i]=file_name1[i+2];
			} 

			 if ((fp2 = fopen(file_namenew, "r"))==NULL)    //open the target xml file
			{
			   printf("CANNOT OPEN the xml file\n");              
			exit(0);                               
			}

			fgets(line1,charsize,fp2);
	
			fgets(line2,charsize,fp2);
		//	printf("%s",line2);
			fgets(line3,charsize,fp2);
		//	printf("%s",line3);
			fgets(line4,charsize,fp2);
		//	printf("%s",line4);
			fgets(line5,charsize,fp2);
		//	printf("%s",line5);
			 xx = 0;
             yy = 0;
			 zz = 0;
 			 for (i=1;i<= (Nparticle2+Nparticle1);i++)
			{
			         //fprintf(fp3,"i = %d\n" ,i);
				fscanf(fp2, "%lf %lf %lf", &x, &y, &z);
				 if (x < 0) xx =  ceil(x) +  xboxsize*0.5;
				 else xx  = floor(x)+ xboxsize*0.5;
				 if (y < 0) yy =  ceil(y) +  yboxsize*0.5;
				 else yy = floor(y)+ yboxsize*0.5;
				 if (z < 0) zz =ceil(z) + zboxsize*0.5;
				 else zz =floor(z) + zboxsize*0.5;
				 if (xx > xboxsize)  xx = xboxsize;
				 else if (xx < 1 )       xx = 1;
				 if (yy > yboxsize)  yy = yboxsize;
				 else if (yy < 1 )        yy = 1;
				 if (zz > zboxsize)  zz = zboxsize;
				 else if (zz < 1 )       zz = 1;
				 if (i <= (Nparticle2+Nparticle1))
				 {
					 if (nflag[i-1] == 1)      densityp[xx-1][yy-1][zz-1] = densityp[xx-1][yy-1][zz-1]+1;
					 else if (nflag[i-1] == 2) densitys[xx-1][yy-1][zz-1] = densitys[xx-1][yy-1][zz-1]+1;
					 else if (nflag[i-1] == 3) densityn[xx-1][yy-1][zz-1] = densityn[xx-1][yy-1][zz-1]+1;
				 }
			 }

				for( i=0; i<xboxsize; i++){
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							density[i][j][q] = densityp[i][j][q] + densitys[i][j][q] + densityn[i][j][q];
						}
					}
				}
				for( i=0; i<xboxsize; i++){
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							if (density[i][j][q]!=0)
							{
							density1[i][j][q] = (double)densityp[i][j][q]/(double)density[i][j][q];
							density2[i][j][q] = (double)densityn[i][j][q]/(double)density[i][j][q];
							density3[i][j][q] = (double)densitys[i][j][q]/(double)density[i][j][q];
							}
							else 
							{
							density1[i][j][q] = 0.0;
							density2[i][j][q] = 0.0;
							density3[i][j][q] = 0.0;
							}
						}
					}
				}

				for( i=0; i<xboxsize; i++){       //initilize the arrays
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							density1total[i][j][q] = density1total[i][j][q] +density1[i][j][q];
							density2total[i][j][q] = density2total[i][j][q] +density2[i][j][q];;
							density3total[i][j][q] = density3total[i][j][q] +density3[i][j][q];;
						}
					}
				}
				for( i=0; i<xboxsize; i++){       //initilize the arrays
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							densityp[i][j][q] = 0;
							densitys[i][j][q] = 0;
							densityn[i][j][q] = 0;
							density[i][j][q]  = 0;
							
							density1[i][j][q] = 0.0;
							density2[i][j][q] = 0.0;
							density3[i][j][q] = 0.0;
						}
					}
				}

			       fclose(fp2);
				   file      =   file     + 1;

                                   printf ("file = %d",file);
    }
	else if ((file % Average) == 0)
	{
		   fscanf(fp1,"%s",file_name1); //read the file name
		   filesize  =  strlen(file_name1);
			for (i=0;i<=(filesize-2);i++)
			{
				file_namenew[i]=file_name1[i+2];
			} 

			 if ((fp2 = fopen(file_namenew, "r"))==NULL)    //open the target xml file
			{
			   printf("CANNOT OPEN the xml file\n");              
			exit(0);                               
			}

		   sprintf(file_namegen,"v.%d.vtk",file_gen); 
		   printf("file_namegen = %s\n",file_namegen); //generate the vtk file name

			if ((fp3 = fopen(file_namegen, "w+"))==NULL)   
		   {
			   printf("CANNOT OPEN file gen\n");             
			   exit(0);                               
			}
		//	printf("file gen\n");
		//write the head lines of the vtk files
			fprintf(fp3,"# vtk DataFile Version 3.1\n");
			fprintf(fp3,"VTK file containing grid data\n");
			fprintf(fp3,"ASCII>\n"); fputc('\n',fp3);

			fprintf(fp3,"DATASET STRUCTURED_POINTS\n");
			fprintf(fp3,"DIMENSIONS   90   240   90\n");
			fprintf(fp3,"ORIGIN    0   0   0\n");
			fprintf(fp3,"SPACING   1   1   1\n"); fputc('\n',fp3);
		     
			fprintf(fp3,"POINT_DATA 1944000\n");
			fprintf(fp3,"SCALARS c float\n");
			fprintf(fp3,"LOOKUP_TABLE default\n");
			// generate the position and type arrey;
			// jump the five head lines of file 1 and file 2
			fgets(line1,charsize,fp2);
			
			fgets(line2,charsize,fp2);
			
			fgets(line3,charsize,fp2);
			
			fgets(line4,charsize,fp2);
			
			fgets(line5,charsize,fp2);
				

			 xx = 0;
             yy = 0;
			 zz = 0;
 			 for (i=1;i<= (Nparticle2+Nparticle1);i++)
			{
			         //fprintf(fp3,"i = %d\n" ,i);
				fscanf(fp2, "%lf %lf %lf", &x, &y, &z);
				 if (x < 0) xx =  ceil(x) +  xboxsize*0.5;
				 else xx  = floor(x)+ xboxsize*0.5;
				 if (y < 0) yy =  ceil(y) +  yboxsize*0.5;
				 else yy = floor(y)+ yboxsize*0.5;
				 if (z < 0) zz =ceil(z) + zboxsize*0.5;
				 else zz =floor(z) + zboxsize*0.5;
				 if (xx > xboxsize)  xx = xboxsize;
				 else if (xx < 1 )       xx = 1;
				 if (yy > yboxsize)  yy = yboxsize;
				 else if (yy < 1 )        yy = 1;
				 if (zz > zboxsize)  zz = zboxsize;
				 else if (zz < 1 )       zz = 1;
				 if (i <= (Nparticle2+Nparticle1))
				 {
					 if (nflag[i-1] == 1)      densityp[xx-1][yy-1][zz-1] = densityp[xx-1][yy-1][zz-1]+1;
					 else if (nflag[i-1] == 2) densitys[xx-1][yy-1][zz-1] = densitys[xx-1][yy-1][zz-1]+1;
					 else if (nflag[i-1] == 3) densityn[xx-1][yy-1][zz-1] = densityn[xx-1][yy-1][zz-1]+1;

				 }

			}

				for( i=0; i<xboxsize; i++){
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							density[i][j][q] = densityp[i][j][q] + densitys[i][j][q] + densityn[i][j][q];
						}
					}
				}
				for( i=0; i<xboxsize; i++){
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							if (density[i][j][q]!=0)
							{
							density1[i][j][q] = (double)densityp[i][j][q]/(double)density[i][j][q];
							density2[i][j][q] = (double)densityn[i][j][q]/(double)density[i][j][q];
							density3[i][j][q] = (double)densitys[i][j][q]/(double)density[i][j][q];
							}
							else 
							{
							density1[i][j][q] = 0.0;
							density2[i][j][q] = 0.0;
							density3[i][j][q] = 0.0;
							}
						}
					}
				}
				for( i=0; i<xboxsize; i++){       //initilize the arrays
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							density1total[i][j][q] = density1total[i][j][q] +density1[i][j][q];
							density2total[i][j][q] = density2total[i][j][q] +density2[i][j][q];;
							density3total[i][j][q] = density3total[i][j][q] +density3[i][j][q];;
						}
					}
				}
				point = 0;

				for( q=0; q<zboxsize; q++){
					for( j=0; j<yboxsize; j++){
						for( i=0; i<xboxsize; i++){
                            density1total[i][j][q] = density1total[i][j][q] / Average;
							fprintf(fp3, "%f\n", density1total[i][j][q]);
							point = point + 1;
						}
					}
				}
              printf("point = %d  \n", point);
				for( i=0; i<xboxsize; i++){       //initilize the arrays
					for( j=0; j<yboxsize; j++){
						for( q=0; q<zboxsize; q++){
							densityp[i][j][q]      = 0;
							densitys[i][j][q]      = 0;
							densityn[i][j][q]      = 0;
							density[i][j][q]       = 0;
							
							density1[i][j][q]      = 0.0;
							density2[i][j][q]      = 0.0;
							density3[i][j][q]      = 0.0;
							density1total[i][j][q] = 0.0;
							density2total[i][j][q] = 0.0;
							density3total[i][j][q] = 0.0;
						}
					}
				}

			       fclose(fp2);fclose(fp3);
				   file_gen  =   file_gen + 1;
				   file      =   file     + 1;
                                   printf ("file = %d",file);
	}
}
    fclose(fp1); //free the file
	   //free the array
    free(nflag);

	    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(densityp[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(densityp[i]);   
    }   
    free(densityp); 

    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(densitys[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(densitys[i]);   
    }   
    free(densitys); 

    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(densityn[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(densityn[i]);   
    }   
    free(densityn); 

    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(density[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(density[i]);   
    }   
    free(density);

    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(density1[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(density1[i]);   
    }   
    free(density1);

    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(density2[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(density2[i]);   
    }   
    free(density2); 

    for(i=0; i<xboxsize; i++) 
    {
        for(j=0; j<yboxsize; j++) 
        {   
            free(density3[i][j]);   
        }   
    }       
    for(i=0; i<xboxsize; i++)   
    {       
        free(density3[i]);   
    }   
    free(density3); 
	return 0;

}
