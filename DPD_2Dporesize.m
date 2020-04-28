%Savefiles
 fid = fopen('015.pdb','r');%file route
 lammps = fopen('v.1.vtk','w');

 
 fprintf(lammps,'# vtk DataFile Version 3.1\n');
 fprintf(lammps,'VTK file containing grid data\n');
 fprintf(lammps,'ASCII>\n\n');
 
 fprintf(lammps,'DATASET STRUCTURED_POINTS\n');
 
 fprintf(lammps,'DIMENSIONS   100   100   100\n');
 fprintf(lammps,'ORIGIN    0   0   0\n');
 fprintf(lammps,'SPACING   1   1   1\n\n');
 
 fprintf(lammps,'POINT_DATA 473864\n');
 fprintf(lammps,'SCALARS c float\n');
 fprintf(lammps,'LOOKUP_TABLE default\n');

    boxsize = [100, 100, 100]; %box size (change here if the box size is changed)
    %fid = fopen('density.pdb','r');%file route

    density1=0.0*ones(boxsize(1), boxsize(2), boxsize(3));
    %point=1;
 
 totallines=444559;
 
    for q = 1:totallines
           data = fgetl(fid);
        arr =textscan(data,'%f %f %f');
        i = floor(arr{1});
        j = floor(arr{2});
        k = floor(arr{3});
        
        density1(i,j,k)=density1(i,j,k)+1;
    end

    
 
    for i = 1 : boxsize(1)
          for j = 1 : boxsize(2)
                for k =1 : boxsize(3)    
    
                     
                       density1(i,j,k)= density1(i,j,k)/3;
  
                    if (density1(i,j,k) ~= 0)
                        disp(density1(i,j,k))
                    end
  
                       fprintf(lammps,'%f\n',density1(i,j,k));
               end 
          end
    end

  

  
fclose('all');   
