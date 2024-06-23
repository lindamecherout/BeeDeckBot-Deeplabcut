# -*- coding: utf-8 -*-

import scipy.stats as stats
import numpy as np

variance_observee = 2.66e-7 # observed variance
n = len(loss[iterations > 2000])  # after 2000 itérations
seuil_variance = 1e-6  # hypothetical threshold

# chi² statistic
chi2_stat = (n - 1) * variance_observee / seuil_variance

# alpha and dregree
alpha = 0.05
chi2_critique = stats.chi2.ppf(1 - alpha, df=n-1)

# comparaison
if chi2_stat < chi2_critique:
    conclusion = "Nous rejetons H0. Les pertes sont stables et ne varient pas significativement."
else:
    conclusion = "Nous ne pouvons pas rejeter H0. Les pertes varient significativement."

chi2_stat, chi2_critique, conclusion
