% load data
data = readtable("C:\Users\Lili\Downloads\triangulated_points_filtered.xlsx");

% extraction coordinates
x_head = str2double(data{2:end, 1});
y_head = -str2double(data{2:end, 7});
z_head = str2double(data{2:end, 13});

x_center = str2double(data{2:end, 2});
y_center = -str2double(data{2:end, 8});
z_center = str2double(data{2:end, 14});

x_back = str2double(data{2:end, 3});
y_back = -str2double(data{2:end, 9});
z_back = str2double(data{2:end, 15});

x_flowright = str2double(data{2:end, 4});
y_flowright = -str2double(data{2:end, 10});
z_flowright = str2double(data{2:end, 16});

x_flowleft = str2double(data{2:end, 5});
y_flowleft = -str2double(data{2:end, 11});
z_flowleft = str2double(data{2:end, 17});

x_flowcenter = str2double(data{2:end, 6});
y_flowcenter = -str2double(data{2:end, 12});
z_flowcenter = str2double(data{2:end, 18});

% create the video
outputVideo = VideoWriter('3D_Scatter_Plot_Video.avi');
outputVideo.FrameRate = 100; % Ajuster le framerate selon les besoins
open(outputVideo);

% create the figure
figure;
xlabel('X');
ylabel('Y');
zlabel('Z');
title('Trajectoire 3D en fonction du temps');
grid on;
axis equal;



for i = 1:length(x_head)
    clf;
    hold on;
    
    % bee
    scatter3(x_head(i), y_head(i), z_head(i), 'b', 'filled'); % Point pour la tête
    scatter3(x_center(i), y_center(i), z_center(i), 'b', 'filled'); % Point pour le centre
    scatter3(x_back(i), y_back(i), z_back(i), 'b', 'filled'); % Point pour le dos
    
    % flower
    scatter3(x_flowright(i), y_flowright(i), z_flowright(i), 'r', 'filled'); % Point pour la droite de la fleur
    scatter3(x_flowleft(i), y_flowleft(i), z_flowleft(i), 'r', 'filled'); % Point pour la gauche de la fleur
    scatter3(x_flowcenter(i), y_flowcenter(i), z_flowcenter(i), 'r', 'filled'); % Point pour le centre de la fleur
   
    
    % capture video
    xlim([0 600]);
    ylim([-500 0]);
    zlim([300 600]);
    view([-10 40]);
    frame = getframe(gcf);
    writeVideo(outputVideo, frame);

    hold off;
end

% close the video
close(outputVideo);
