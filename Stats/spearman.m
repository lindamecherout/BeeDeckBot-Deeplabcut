import pandas as pd
from scipy.stats import spearmanr

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

resultats_spearman = []

# spearman correlation
for col_cam, col_mir in paires:
    corr, p_value = spearmanr(data[col_cam], data[col_mir])
    resultats_spearman.append((col_cam, col_mir, corr, p_value))

resultats_spearman_df = pd.DataFrame(resultats_spearman, columns=['Colonne_cam', 'Colonne_mir', 'Corrélation', 'P_valeur'])

# results
resultats_spearman_df
