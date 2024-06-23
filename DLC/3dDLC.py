# -*- coding: utf-8 -*-
# don't forget to set the environment

import deeplabcut
import os
from pathlib import Path
import matplotlib

# creating the project
YourName = 'lili'
YourExperimentName = 'testbee3d'
config_path = deeplabcut.create_new_project_3d(YourExperimentName,YourName, working_directory="C:\\Users\\Lili\\Desktop\\DLC\\test 2\\3d", num_cameras=2)
config_path3d = os.path.join(os.getcwd(),"C:\\Users\\Lili\\Desktop\\DLC\\test 2\\3d\\bee3d2-lili-2024-04-16-3d\\config.yaml")

# deeplabcut calibration
deeplabcut.calibrate_cameras(config_path3d, cbrow =8,cbcol =5,calibrate=False,alpha=0.9)
deeplabcut.calibrate_cameras(config_path3d, cbrow =8,cbcol =5,calibrate=True,alpha=0.9)
deeplabcut.check_undistortion(config_path3d, cbrow =8,cbcol =5)

# change the bodyparts in the .yaml file compared to your DLC2d and put the paths for the 2d config.yaml (camera with mirror and camera without mirror)
videos3D = 
deeplabcut.triangulate(config_path3d, videos3D, filterpredictions=True)

# 3D trajectory visualization
deeplabcut.create_labeled_video_3d(config_path, ['yourDLC_3D_scorername.h5'], videotype=".MP4")
