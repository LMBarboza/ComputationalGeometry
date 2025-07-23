import torch
import torch.nn as nn


class MLP(nn.Module):
    def __init__(self, state_size: int, actions_size: int) -> None:
        super().__init__()
        self.layers = nn.Sequential(
            nn.Linear(state_size, 256),
            nn.ReLU(),
            nn.Linear(256, 128),
            nn.ReLU(),
            nn.Linear(128, actions_size),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = self.layers(x)
        return x
