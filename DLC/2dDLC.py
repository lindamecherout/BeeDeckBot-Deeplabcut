# -*- coding: utf-8 -*-
# don't forget to set the environment
import deeplabcut

# creating the project .yaml
projet="2dbeetestdroite"
experimentateur="lili"
working_directory="C:\\Users\\Lili\\Desktop\\STAGE ISM\\DLC\\test 2\\2d"
deeplabcut.create_new_project(projet, experimentateur, ["C:\\Users\\Lili\\Desktop\\STAGE ISM\\DLC\\test 2\\video_droite\\camera-1-01.MP4", "C:\\Users\\Lili\\Desktop\\STAGE ISM\\DLC\\test 2\\video_droite\\camera-1-02.MP4"], working_directory, copy_videos=True, multianimal=False)
 
config="C:\\Users\\Lili\\Desktop\\STAGE ISM\\DLC\\test 2\\2d\\2dbeetest2droites-lili-2024-04-23\\config.yaml"


# deeplabcut labeling with napari (be sure that all the key points are here)
deeplabcut.label_frames(config)
 
deeplabcut.check_labels(config, visualizeindividuals=True)

# deeplabcut training
deeplabcut.create_training_dataset(config, augmenter_type='imgaug')
 
deeplabcut.train_network(config, trainingsetindex=0, gputouse=None, max_snapshots_to_keep=5, autotune=False, displayiters=100, saveiters=15000, maxiters=30000, allow_growth=True)

# deeplabcut training evaluation
deeplabcut.evaluate_network(config, Shuffles=[1], plotting=True)


# videos analysis
videos = 'fullpath/analysis/project/videos'

deeplabcut.analyze_videos(config, videos, videotype='.MP4', shuffle=1, trainingsetindex=0, gputouse=None, save_as_csv=True, destfolder=None, dynamic=(True, .5, 10))

deeplabcut.filterpredictions(config, videos, videotype='.MP4',filtertype= 'median')

deeplabcut.plot_trajectories(config, videos, videotype='.MP4')