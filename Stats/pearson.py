# -*- coding: utf-8 -*-


import pandas as pd
from scipy.stats import pearsonr

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


resultats = []

# pearson correlation
for col_cam, col_mir in paires:
    corr, p_value = pearsonr(data[col_cam], data[col_mir])
    resultats.append((col_cam, col_mir, corr, p_value))

# dataframe
resultats_df = pd.DataFrame(resultats, columns=['Colonne_cam', 'Colonne_mir', 'Corrélation', 'P_valeur'])

import ace_tools as tools; tools.display_dataframe_to_user(name="Résultats de Corrélation", dataframe=resultats_df)

# results
resultats_df
