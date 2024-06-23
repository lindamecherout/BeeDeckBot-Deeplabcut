% load
input_folder = "C:\Users\Lili\Desktop\STAGE ISM\DLC\test 8\video_absolutegauche";
output_folder = "C:\Users\Lili\Desktop\STAGE ISM\DLC\test 8";
mirror_all_videos(input_folder, output_folder);

function mirror_all_videos(input_folder, output_folder)
    if ~exist(output_folder, 'dir')
        mkdir(output_folder);
    end

    % videos listing
    video_files = dir(fullfile(input_folder, '*.mp4')); % Changez l'extension si nécessaire

    for k = 1:length(video_files)
        input_path = fullfile(input_folder, video_files(k).name);
        output_path = fullfile(output_folder, video_files(k).name);

        fprintf('Processing %s...\n', input_path);

        % miroir inversion
        mirror_video(input_path, output_path);
    end
end

function mirror_video(input_path, output_path)
    % VideoReader object
    video_reader = VideoReader(input_path);
    
    % VideoWriter object
    video_writer = VideoWriter(output_path, 'MPEG-4');
    video_writer.FrameRate = video_reader.FrameRate; % Assurez-vous que le frame rate est le même
    open(video_writer);

    while hasFrame(video_reader)
        frame = readFrame(video_reader);
        
        % application of the inversion
        mirrored_frame = flip(frame, 2);
        
        writeVideo(video_writer, mirrored_frame);
    end
    close(video_writer);
end
