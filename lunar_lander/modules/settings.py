import torch

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
NUM_EPISODES = 600
MODEL_PATH = "lunar_lander.pth"

GAMMA = 0.99
EPS_START = 0.9
EPS_END = 0.05
EPS_DECAY = 1000
TAU = 0.005
LR = 1e-2

MEMORY_SIZE = 10000
BATCH_SIZE = 128
