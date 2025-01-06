from netpyne import sim
from tut5 import netParams, simConfig

# Network parameters
sim.createSimulateAnalyze(netParams, simConfig)

import numpy as np
import matplotlib.pyplot as plt

# 스파이크 데이터 가져오기
spike_times = sim.allSimData['spkt']  # 스파이크 시간
spike_ids = sim.allSimData['spkid']  # 스파이크가 발생한 뉴런의 ID

# 각 층의 뉴런 ID 정의 (예: Layer 2와 Layer 5의 ID 범위)
layer_2_ids = range(0, 100)  # Layer 2의 뉴런 ID (예: 0 ~ 99)
layer_5_ids = range(200, 300)  # Layer 5의 뉴런 ID (예: 100 ~ 199)

#  Layer 2 스파이크 데이터 필터링
layer_2_spike_times = [time for time, id in zip(spike_times, spike_ids) if id in layer_2_ids]
layer_2_spike_ids = [id for id in spike_ids if id in layer_2_ids]

# Layer 5 스파이크 데이터 필터링
layer_5_spike_times = [time for time, id in zip(spike_times, spike_ids) if id in layer_5_ids]
layer_5_spike_ids = [id for id in spike_ids if id in layer_5_ids]

# 스파이크 추이 그래프 생성
plt.figure(figsize=(12, 6))

# Layer 2 스파이크 시각화
plt.scatter(layer_2_spike_times, layer_2_spike_ids, label="Layer 2", alpha=0.7)

# Layer 5 스파이크 시각화
plt.scatter(layer_5_spike_times, layer_5_spike_ids, label="Layer 5", alpha=0.7)

# 그래프 설정
plt.title("Spike Trends in Layers 2 and 5")
plt.xlabel("Time (ms)")
plt.ylabel("Neuron ID")
plt.legend()
plt.grid(True)
plt.show()

