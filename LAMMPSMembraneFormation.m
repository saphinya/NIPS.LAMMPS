%directory = '~/Documents/lammps/files/';
condition = 'real302 0.45 MDPD 12% C30P50 addi6 t = ';
fid = fopen('real302.profile','r');%file route
for z=1:4
    data = fgets(fid);
end


for q = 1 : 1000
    %file = strcat('Q_',num2str(q),'.xml') ;
    %disp(file);
    %filepath = strcat(directory,file);
    figure1 = figure;
    %disp(filepath);
    boxsize = [165, 100, 100]; %box size (change here if the box size is changed)
    %fid = fopen('density.pdb','r');%file route
    time = q*10000;
    outputname =  strcat(condition,num2str(time),'.jpg');%name of saved figure
    density1=0.0*ones(boxsize(1), boxsize(2), boxsize(3));
    %point=1;
    for i = 1 : boxsize(1)
          for j = 1 : boxsize(2)
                for k =1 : boxsize(3)
                    data = fgets(fid);
                    arr =textscan(data,'%f %f %f %f %f %f');
                    
                    if (arr{6} ~= 0)
                        disp(arr{6});
                    end
                    
                    density1(i,j,k)= arr{6}/3;
                    %point=point+1;
                end 
          end
    end
    density1 = smooth3(density1, 'box', 3);
       [YY, XX, ZZ] = meshgrid(1:size(density1,2), 1:size(density1,1), 1:size(density1,3));
       XX = 1.174*(((XX-1)*size(density1,1)/(size(density1,1)-1))-60);                                                                        
      YY = 1.174*((YY-1)*size(density1,2)/(size(density1,2)-1));
      ZZ = 1.174*((ZZ-1)*size(density1,3)/(size(density1,3)-1));
    h=patch(isosurface(XX,YY,ZZ,density1,0.45), 'FaceColor', 'yellow', 'EdgeColor', 'none');
    set(gca,'FontSize',17,'FontWeight','b','FontName','Times New Roman','xtick',(-80:20:120),'ytick',(0:30:120),'ztick',(0:30:120));
    %set(gca,'xtick',[],'ytick',[],'ztick',[])
    patch(isocaps(XX,YY,ZZ,density1,0.45), 'FaceColor', 'yellow', 'EdgeColor', 'none');
    %view([-35 15])
    view([-5 15])
    %view([-22 21])
    %view([-14 21])
    %xlabel('y','fontsize',18,'fontweight','b')
    %ylabel('x','fontsize',18,'fontweight','b')
    %zlabel('z','fontsize',18,'fontweight','b')
    axis([-80 120 0 120 0 120])  %boxsize
    % set(gca,'xtick',[],'ytick',[],'ztick',[]);
    % axis vis3d
    camlight;lighting phong;
    axis on     %turns on all axis lines, tick marks, and labels
    grid on     %adds major grid lines to the current axe
    hold on     %retains the current graph and adds another graph to it.
    box on      %displays the boundary of the current axes.
    ax = gca;
    ax.BoxStyle = 'full';
%xlabel('x','Position',[-50,-50,50],'FontName','Times New Roman','fontsize',18,'fontweight','bold');%??????
%ylabel('y','Position',[30,-140,50],'FontName','Times New Roman','fontsize',18,'fontweight','bold');%
%zlabel('z','Position',[-35,-40,150],'FontName','Times New Roman','fontsize',18,'fontweight','bold');%
% datacoagulation=datacoagulation60w;
% x1=datacoagulation(:,1);
% y1=datacoagulation(:,2);
% z1=datacoagulation(:,3);
% scatter3(y1+70,x1+45,z1+45,2,'y','filled')%????
% Second step??draw the line and face of the boundary
    %a=[5 5 5 5 5];b=[0 0 5.5 5.5 0];c=[0 5.5 5.5 0 0];
    %plot3(a,b,c,'--r','LineWidth',2)%'-.r'??????(??)??':r'????(??),'--r'????(??)
    %hold on

    aa=0:10:120;
    bb=aa;
    [aa,bb]=meshgrid(aa,bb);
    cc=aa*0;
    g1=surf(cc,aa,bb);
    set(g1,'edgecolor','none','FaceColor','y');
    alpha(g1,0.1); %set transparency 
  
    
    saveas(figure1, outputname)
    close(figure1);
    
    for z1=1:1
    data = fgets(fid);
    end
end

fclose(fid);
