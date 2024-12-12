import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from scipy.stats import poisson

# get random numbers that are poisson deviated
data_set = np.random.poisson(4, 2000)

# the bins have to be kept as a positive integer because poisson is a positive integer distribution
bins = np.arange(20) - 0.5
entries, bin_edges, patches = plt.hist(data_set, bins=bins, density=True, label='Data')

# calculate bin centers
middles_bins = (bin_edges[1:] + bin_edges[:-1]) * 0.5


def fit_function(k, lamb):
    # The parameter lamb will be used as the fit parameter
    return poisson.pmf(k, lamb)


# fit with curve_fit
parameters, cov_matrix = curve_fit(fit_function, middles_bins, entries)

# plot poisson-deviation with fitted parameter
x_plot = np.arange(0, 100)

plt.plot(
    x_plot,
    fit_function(x_plot, *parameters),
    marker='D', linestyle='-',
    color='red',
    label='Fit result',
)
plt.yscale('log')  # 设置纵轴为对数刻度
plt.legend()
plt.savefig('poisson_fit.png')
