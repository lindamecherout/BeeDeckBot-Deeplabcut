% load Excel files
data1 = readtable("C:\Users\Lili\Downloads\traingulation filtrée\camera-1-05DLC_resnet50_2dbeetestdroiteJun2shuffle1_5000_filtered.xlsx");
data2 = readtable('C:\Users\Lili\Downloads\traingulation filtrée\camera-2-05DLC_resnet50_2dbeetestgaucheJun2shuffle1_5000_filtered.xlsx');

% extract coordinates
beeheadx = data1{3:end, 2}; % Axe X
beecenterx = data1{3:end, 5}; % Axe X
beebackx = data1{3:end, 8}; % Axe X
flowrightx = data1{3:end, 11}; % Axe X
flowleftx = data1{3:end, 14}; % Axe X
flowcenterx = data1{3:end, 17}; % Axe X

beeheady = data1{3:end, 3}; % Axe Y
beecentery = data1{3:end, 6}; % Axe Y
beebacky = data1{3:end, 9}; % Axe Y
flowrighty = data1{3:end, 12}; % Axe Y
flowlefty = data1{3:end, 15}; % Axe Y
flowcentery = data1{3:end, 18}; % Axe Y

beeheadz = data2{3:end, 3}; % Axe Z
beecenterz = data2{3:end, 6}; % Axe Z
beebackz = data2{3:end, 9}; % Axe Z
flowrightz = data2{3:end, 12}; % Axe Z
flowleftz = data2{3:end, 15}; % Axe Z
flowcenterz = data2{3:end, 18}; % Axe Z

% combine coordinates to form points in 3D
points3D = [beeheadx, beecenterx, beebackx, flowrightx, flowleftx, flowcenterx, beeheady, beecentery, beebacky, flowrighty, flowlefty, flowcentery, beeheadz, beecenterz, beebackz, flowrightz, flowleftz, flowcenterz];
points3D_table = array2table(points3D, 'VariableNames', {'beeheadx', 'beecenterx', 'beebackx', 'flowrightx', 'flowleftx', 'flowcenterx', 'beeheady', 'beecentery', 'beebacky', 'flowrighty', 'flowlefty', 'flowcentery', 'beeheadz', 'beecenterz', 'beebackz', 'flowrightz', 'flowleftz', 'flowcenterz'});

% save as CSV
writetable(points3D_table, 'triangulated_points_filtered.csv');
