import re
import matplotlib.pyplot as plt
import numpy as np

# 读取日志文件
with open('run_p_nano.log', 'r') as file:
    log_data = file.readlines()

# 提取添加时间
adding_times = []
for line in log_data:
    match = re.search(r'Duration: (\d+) ns', line)
    if match:
        adding_times.append(float(match.group(1)))

# 计算90%分位数
percentile_90 = np.percentile(adding_times, 90)
print(f'90%分位数: {percentile_90}ns')

# 计算99%分位数
percentile_99 = np.percentile(adding_times, 99)
print(f'99%分位数: {percentile_99}ns')

# 定义区间
bins = np.arange(0, 51000, 1000)
bins = np.append(bins, [float('inf')])  # 添加一个无限大的区间

# 统计每个区间的频率
hist, bin_edges = np.histogram(adding_times, bins=bins)

# 打印每个区间的频率
# for i in range(len(hist)):
#     if i == len(hist) - 1:
#         print(f'{bin_edges[i]} ns 及以上: {hist[i]}')
#     else:
#         print(f'{bin_edges[i]} ns - {bin_edges[i+1]} ns: {hist[i]}')

# 绘制直方图
plt.hist(adding_times, bins=bin_edges, edgecolor='black')
plt.axvline(percentile_90, color='r', linestyle='dashed', linewidth=1, label=f'90% percent number: {percentile_90}ns')
plt.axvline(percentile_99, color='b', linestyle='dashed', linewidth=1, label=f'99% percent number: {percentile_99}ns')
plt.xlabel('cost Time for one update (ns)')
plt.ylabel('Update(Add) Edge Frequency')
plt.yscale('log')  # 设置纵轴为对数刻度
plt.title('Distribution of Adding Times')
plt.legend()

# 标注 50000 ns 及以上的数据量
plt.text(51000, max(hist) * 0.8, f'50000 ns 及以上: {hist[-1]}', color='black', ha='left')

plt.savefig('adding_times_distribution_Nano2.png')
plt.show()