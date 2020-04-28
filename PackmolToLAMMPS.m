%polymer
 molecules=2400;
 length=100;
 bond=(length-1);
 %angle=(length-2);
 bead=molecules*length;
 tbond=molecules*bond;
 %tangle=molecules*angle;
 
 %Savefiles
 packmol = fopen('dpdbond90c08.pdb','r');
 lammps = fopen('dpdbond100c08.data','w');
 tlines = cell(0,1);
 
 fprintf(lammps,'LAMMPS Description\n\n');
 fprintf(lammps,'240000 atoms\n');
 fprintf(lammps,'237600 bonds\n\n');
 %fprintf(lammps,'297920 angles\n\n');
 
 fprintf(lammps,'4  atom types\n');
 fprintf(lammps,'1  bond types\n\n');
 %fprintf(lammps,'1  angle types\n\n');
 
 fprintf(lammps,'-30.0 105.0 xlo xhi\n');
 fprintf(lammps,' 0 100.0 ylo yhi\n');
 fprintf(lammps,' 0 100.0 zlo zhi\n\n');
 
 fprintf(lammps,'Masses\n\n');
 fprintf(lammps,'1 1\n');
 fprintf(lammps,'2 1\n');
 fprintf(lammps,'3 1\n');
 fprintf(lammps,'4 100000\n\n');

 
 %fprintf(lammps,'Atoms# atom-type x y z molecule-ID rho\n\n');
 fprintf(lammps,'Atoms# molecule-ID atom-type x y z\n\n');
 
 
 %XYZ----------------------------------------------------------------------
 
 %polymer-XYZ-------------------------
for i = 1:bead
   
   data = fgetl(packmol);
   disp(data);
   
   arr = textscan(data,'%f %f %f');
   disp(arr);
  
   %fprintf(lammps,'%i %i %f %f %f %i %i\n', i,1,arr{1},arr{2},arr{3},1+fix((i/length)-(1/length)),0);
   fprintf(lammps,'%i %i %i %f %f %f\n', i,1+fix((i/length)-(1/length)),1,arr{1},arr{2},arr{3});
   
end
%additive-XYZ-------------------------


%BOND----------------------------------------------------------------------

 %polymer-BOND-------------------------
fprintf(lammps,'\nBonds\n\n');
for h = 1:tbond
fprintf(lammps,'%i %i %i %i\n', h , 1, h+fix((h/bond)-(1/bond)), h+1+fix((h/bond)-(1/bond)));
end




%ANGLE----------------------------------------------------------------------

%polymer-ANGLE-------------------------
%fprintf(lammps,'\nAngles\n\n');
%for w = 1:tangle
%fprintf(lammps,'%i %i %i %i %i\n', w , 1, w+2*fix((w/angle)-(1/angle)), w+1+2*fix((w/angle)-(1/angle)), w+2+2*fix((w/angle)-(1/angle)));
%end


fclose('all');   
