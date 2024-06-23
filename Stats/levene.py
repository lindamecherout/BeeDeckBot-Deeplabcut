# -*- coding: utf-8 -*-

import pandas as pd
from scipy.stats import levene

# load data
filtered_data_path = '/mnt/data/triangulated_points_filtered.xlsx'
non_filtered_data_path = '/mnt/data/triangulated_points.xlsx'

filtered_data = pd.read_excel(filtered_data_path)
non_filtered_data = pd.read_excel(non_filtered_data_path)

filtered_columns = filtered_data[['beeheadx', 'beecenterx', 'beebackx', 'beeheady', 'beecentery', 'beebacky', 'beeheadz', 'beecenterz', 'beebackz']]
non_filtered_columns = non_filtered_data[['beeheadx', 'beecenterx', 'beebackx', 'beeheady', 'beecentery', 'beebacky', 'beeheadz', 'beecenterz', 'beebackz']]

# replace NaN ​​with mean in unfiltered data
non_filtered_columns_filled = non_filtered_columns.fillna(non_filtered_columns.mean())

# same but with flower
filtered_columns_flow = filtered_data[['flowrightx', 'flowleftx', 'flowcenterx', 'flowrighty', 'flowlefty', 'flowcentery', 'flowrightz', 'flowleftz', 'flowcenterz']]
non_filtered_columns_flow = non_filtered_data[['flowrightx', 'flowleftx', 'flowcenterx', 'flowrighty', 'flowlefty', 'flowcentery', 'flowrightz', 'flowleftz', 'flowcenterz']]

# same
non_filtered_columns_flow_filled = non_filtered_columns_flow.fillna(non_filtered_columns_flow.mean())

# combine bee and flow columns into single dataframes for filtered and unfiltered data
filtered_combined = pd.concat([filtered_columns, filtered_columns_flow], axis=1)
non_filtered_combined = pd.concat([non_filtered_columns_filled, non_filtered_columns_flow_filled], axis=1)

# variances
variances_filtered_combined = filtered_combined.var()
variances_non_filtered_combined = non_filtered_combined.var()

# levene test de Levene
levene_results_combined = {}
for column in filtered_combined.columns:
    stat, p_value = levene(filtered_combined[column], non_filtered_combined[column])
    levene_results_combined[column] = {'stat': stat, 'p_value': p_value}

variances_combined_df = pd.DataFrame({
    'Filtered Variance': variances_filtered_combined,
    'Non-Filtered Variance': variances_non_filtered_combined
})

levene_results_combined_df = pd.DataFrame(levene_results_combined).T

import ace_tools as tools
tools.display_dataframe_to_user(name="Combined Variances Comparison", dataframe=variances_combined_df)
tools.display_dataframe_to_user(name="Combined Levene's Test Results", dataframe=levene_results_combined_df)

# results
variances_combined_df, levene_results_combined_df
