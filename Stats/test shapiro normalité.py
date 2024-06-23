# -*- coding: utf-8 -*-

import pandas as pd
from scipy.stats import shapiro

# load data
file_path = '/mnt/data/Classeur2.xlsx'
data = pd.read_excel(file_path, sheet_name='Feuil1', skiprows=1)  # Ignorer la première ligne

# pairing
paires = [
    ('beehead_x_cam', 'beehead_x_mir'),
    ('beecenter_x_cam', 'beecenter_x_mir'),
    ('beeback_x_cam', 'beeback_x_mir'),
    ('flowright_x_cam', 'flowright_x_mir'),
    ('flowleft_x_cam', 'flowleft_x_mir'),
    ('flowcenter_x_cam', 'flowcenter_x_mir')
]

# normality
normality_results = []
for col_cam, col_mir in paires:
    stat_cam, p_cam = shapiro(data[col_cam])
    stat_mir, p_mir = shapiro(data[col_mir])
    normality_results.append((col_cam, p_cam, col_mir, p_mir))

normality_df = pd.DataFrame(normality_results, columns=['Colonne_cam', 'P_valeur_cam', 'Colonne_mir', 'P_valeur_mir'])

# results
normality_df
