# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# load data
file_path = 'C:\\Users\\Lili\\Downloads\\learning_statsgauche.xlsx'

learning_stats_df = pd.read_excel(file_path)

# extraction
iterations = learning_stats_df.iloc[:, 0]  # Première colonne pour les itérations
loss = learning_stats_df.iloc[:, 1]  # Deuxième colonne pour les pertes

# after 2000 itérations
loss_after_2000 = loss[iterations > 2000]

# mean and SD
mean_loss = np.mean(loss_after_2000)
std_loss = np.std(loss_after_2000)

print(f"Moyenne des pertes après 2000 itérations : {mean_loss}")
print(f"Écart-type des pertes après 2000 itérations : {std_loss}")

# loss function 
plt.figure(figsize=(10, 6))
plt.plot(iterations, loss, label='Training Loss')
plt.xlabel('Iterations')
plt.ylabel('Loss')
plt.title('Training Loss over Iterations')
plt.legend()
plt.grid(True)
plt.show()
