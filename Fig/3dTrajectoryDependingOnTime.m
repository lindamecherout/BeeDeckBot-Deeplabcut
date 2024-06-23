% load data
data = readtable("C:\Users\Lili\Downloads\triangulated_points.xlsx");

% extract coordinates and matrix
beehead = str2double(table2array(data(:, {'beeheadx', 'beeheady', 'beeheadz'})));
beecenter = str2double(table2array(data(:, {'beecenterx', 'beecentery', 'beecenterz'})));
beeback = str2double(table2array(data(:, {'beebackx', 'beebacky', 'beebackz'})));
flowright = str2double(table2array(data(:, {'flowrightx', 'flowrighty', 'flowrightz'})));
flowleft = str2double(table2array(data(:, {'flowleftx', 'flowlefty', 'flowleftz'})));
flowcenter = str2double(table2array(data(:, {'flowcenterx', 'flowcentery', 'flowcenterz'})));

% verification
disp('Dimensions et échantillons des matrices :');
disp(size(beehead));
disp(beehead(1:5, :));
disp(size(beecenter));
disp(beecenter(1:5, :));
disp(size(beeback));
disp(beeback(1:5, :));
disp(size(flowright));
disp(flowright(1:5, :));
disp(size(flowleft));
disp(flowleft(1:5, :));
disp(size(flowcenter));
disp(flowcenter(1:5, :));

% suppress NaN 
beehead = beehead(~any(isnan(beehead), 2), :);
beecenter = beecenter(~any(isnan(beecenter), 2), :);
beeback = beeback(~any(isnan(beeback), 2), :);
flowright = flowright(~any(isnan(flowright), 2), :);
flowleft = flowleft(~any(isnan(flowleft), 2), :);
flowcenter = flowcenter(~any(isnan(flowcenter), 2), :);

% verification
assert(all(~isnan(beehead(:))), 'beehead contient des valeurs NaN');
assert(all(~isnan(beecenter(:))), 'beecenter contient des valeurs NaN');
assert(all(~isnan(beeback(:))), 'beeback contient des valeurs NaN');
assert(all(~isnan(flowright(:))), 'flowright contient des valeurs NaN');
assert(all(~isnan(flowleft(:))), 'flowleft contient des valeurs NaN');
assert(all(~isnan(flowcenter(:))), 'flowcenter contient des valeurs NaN');

% create the figure
figure;
hold on;

% trace the trajectory
plot3(beehead(:,1), beehead(:,2), beehead(:,3), 'b', 'DisplayName', 'Bee Head');
plot3(beecenter(:,1), beecenter(:,2), beecenter(:,3), 'b', 'DisplayName', 'Bee Center');
plot3(beeback(:,1), beeback(:,2), beeback(:,3), 'b', 'DisplayName', 'Bee Back');
plot3(flowright(:,1), flowright(:,2), flowright(:,3), 'r', 'DisplayName', 'Flow Right');
plot3(flowleft(:,1), flowleft(:,2), flowleft(:,3), 'r', 'DisplayName', 'Flow Left');
plot3(flowcenter(:,1), flowcenter(:,2), flowcenter(:,3), 'r', 'DisplayName', 'Flow Center');

% labels
xlabel('x');
ylabel('y');
zlabel('z');
set(gca, 'YDir', 'reverse');
set(gca, 'ZDir', 'reverse');
grid on;

% figure
hold off;
