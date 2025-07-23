import math
import random
import torch
import torch.nn as nn
import torch.optim as optim

import settings
from model import MLP
from replay_memory import ReplayMemory, Transition


class Agent:
    def __init__(self, state_size: int, action_size: int) -> None:
        self.action_size = action_size
        self.device = settings.DEVICE

        self.policy_net = MLP(state_size, action_size).to(self.device)
        self.target_net = MLP(state_size, action_size).to(self.device)
        self.target_net.load_state_dict(self.policy_net.state_dict())
        self.target_net.eval()

        self.optimizer = optim.AdamW(
            self.policy_net.parameters(), lr=settings.LR, amsgrad=True
        )
        self.memory = ReplayMemory()
        self.steps_done = 0

    def select_action(self, state, train=True) -> torch.Tensor:
        if train:
            sample = random.random()
            eps_threshold = settings.EPS_END + (
                settings.EPS_START - settings.EPS_END
            ) * math.exp(-1.0 * self.steps_done / settings.EPS_DECAY)
            self.steps_done += 1
            if sample > eps_threshold:
                with torch.no_grad():
                    return self.policy_net(state).max(1)[1].view(1, 1)
            else:
                return torch.tensor(
                    [[random.randrange(self.action_size)]],
                    device=self.device,
                    dtype=torch.long,
                )
        else:
            with torch.no_grad():
                return self.policy_net(state).max(1)[1].view(1, 1)

    def optimize_model(self):
        if len(self.memory) < settings.BATCH_SIZE:
            return

        transitions = self.memory.sample(settings.BATCH_SIZE)
        batch = Transition(*zip(*transitions))

        non_final_mask = torch.tensor(
            tuple(map(lambda s: s is not None, batch.next_state)),
            device=self.device,
            dtype=torch.bool,
        )
        non_final_next_states = torch.cat(
            [s for s in batch.next_state if s is not None]
        )

        state_batch = torch.cat(batch.state)
        action_batch = torch.cat(batch.action)
        reward_batch = torch.cat(batch.reward)

        state_action_values = self.policy_net(state_batch).gather(1, action_batch)

        next_state_values = torch.zeros(settings.BATCH_SIZE, device=self.device)
        with torch.no_grad():
            next_state_values[non_final_mask] = self.target_net(
                non_final_next_states
            ).max(1)[0]

        expected_state_action_values = (
            next_state_values * settings.GAMMA
        ) + reward_batch

        criterion = nn.SmoothL1Loss()
        loss = criterion(state_action_values, expected_state_action_values.unsqueeze(1))

        self.optimizer.zero_grad()
        loss.backward()
        torch.nn.utils.clip_grad_value_(self.policy_net.parameters(), 100)
        self.optimizer.step()

    def update_target_net(self) -> None:
        target_net_state_dict = self.target_net.state_dict()
        policy_net_state_dict = self.policy_net.state_dict()
        for key in policy_net_state_dict:
            target_net_state_dict[key] = policy_net_state_dict[
                key
            ] * settings.TAU + target_net_state_dict[key] * (1 - settings.TAU)
        self.target_net.load_state_dict(target_net_state_dict)

    def save_model(self, path=settings.MODEL_PATH) -> None:
        torch.save(self.policy_net.state_dict(), path)
        print(f"Model saved to {path}")

    def load_model(self, path=settings.MODEL_PATH) -> None:
        self.policy_net.load_state_dict(torch.load(path, map_location=self.device))
        self.target_net.load_state_dict(self.policy_net.state_dict())
        self.policy_net.eval()
        print(f"Model loaded from {path}")
