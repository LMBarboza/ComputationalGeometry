import gymnasium as gym
import torch
import time

from modules import settings
from modules.agent import Agent


def main() -> None:
    env = gym.make("LunarLander-v3", render_mode="human")

    state, info = env.reset()
    state_size = len(state)
    action_size = env.action_space.n

    agent = Agent(state_size, action_size)
    agent.load_model(settings.MODEL_PATH)

    print("Running simulation with trained model...")
    for i_episode in range(10):
        state, info = env.reset()
        state = torch.tensor(
            state, dtype=torch.float32, device=settings.DEVICE
        ).unsqueeze(0)
        total_reward = 0
        done = False

        while not done:
            action = agent.select_action(state, train=False)

            observation, reward, terminated, truncated, _ = env.step(action.item())
            total_reward += reward
            done = terminated or truncated

            if not done:
                state = torch.tensor(
                    observation, dtype=torch.float32, device=settings.DEVICE
                ).unsqueeze(0)

            time.sleep(0.02)

        print(f"Episode {i_episode + 1}: Total Reward = {total_reward:.2f}")

    env.close()
    print("Simulation finished.")


if __name__ == "__main__":
    main()
