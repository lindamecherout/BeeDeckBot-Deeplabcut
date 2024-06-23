% path
chemin_dossier = "C:\Users\Lili\Desktop\STAGE ISM\DLC\test 8";

% folders
if ~exist('video_miroir', 'dir')
   mkdir('video_miroir')
end

if ~exist('video_sansmiroir', 'dir')
   mkdir('video_sansmiroir')
end

% MP4 listing
liste_videos = dir(fullfile(chemin_dossier, '*.mp4'));

for idx = 1:length(liste_videos)
    video = VideoReader(fullfile(chemin_dossier, liste_videos(idx).name));
    
    % VideoWriter object
    video_miroir= VideoWriter(fullfile('video_miroir', liste_videos(idx).name), 'MPEG-4');
    video_sansmiroir = VideoWriter(fullfile('video_sansmiroir', liste_videos(idx).name), 'MPEG-4');
    
    % frame
    video_miroir.FrameRate = video.FrameRate;
    video_sansmiroir.FrameRate = video.FrameRate;
    
    open(video_miroir);
    open(video_sansmiroir);
    
    while hasFrame(video)
        img = readFrame(video);
        
        % cut
        [hauteur, largeur, ~] = size(img);
        img_miroir = img(:, 1:floor(largeur/2), :);
        img_sansmiroir = img(:, floor(largeur/2)+1:end, :);
        
        writeVideo(video_miroir, img_miroir);
        writeVideo(video_sansmiroir, img_sansmiroir);
    end
    
    close(video_miroir);
    close(video_sansmiroir);
end

% videos folders
chemin_miroir = 'C:\Users\Lili\Desktop\STAGE ISM\DLC\test 7\calib2\video_miroir';
chemin_sansmiroir = 'C:\Users\Lili\Desktop\STAGE ISM\DLC\test 7\calib2\video_sansmiroir';

% rename mirror
video_miroir = dir(fullfile(chemin_miroir, '*.mp4'));
for idx = 1:length(video_miroir)
    fichier = video_miroir(idx).name;
    nouveau_nom = sprintf('camera-2-%02d.mp4', idx);
    nouveau_chemin = fullfile(chemin_miroir, nouveau_nom);
    movefile(fullfile(chemin_miroir, fichier), nouveau_chemin);
    fprintf('Renommé %s en %s\n', fichier, nouveau_nom);
end

% rename without mirror
video_sansmiroir = dir(fullfile(chemin_sansmiroir, '*.mp4'));
for idx = 1:length(video_sansmiroir)
    fichier = video_sansmiroir(idx).name;
    nouveau_nom = sprintf('camera-1-%02d.mp4', idx);
    nouveau_chemin = fullfile(chemin_sansmiroir, nouveau_nom);
    movefile(fullfile(chemin_sansmiroir, fichier), nouveau_chemin);
    fprintf('Renommé %s en %s\n', fichier, nouveau_nom);
end
