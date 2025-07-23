import gym
import torch
from itertools import count

from modules import settings
from modules.agent import Agent


def main() -> None:
    env = gym.make("LunarLander-v2")
    device = settings.DEVICE

    action_size = env.action_space.n
    state, info = env.reset()
    state_size = len(state)

    agent = Agent(state_size, action_size)

    episode_rewards = []

    print("Starting training...")
    for i_episode in range(settings.NUM_EPISODES):
        state, info = env.reset()
        state = torch.tensor(state, dtype=torch.float32, device=device).unsqueeze(0)
        total_reward = 0

        for _ in count():
            action = agent.select_action(state)
            observation, reward, terminated, truncated, _ = env.step(action.item())
            total_reward += reward
            reward = torch.tensor([reward], device=device)
            done = terminated or truncated

            if terminated:
                next_state = None
            else:
                next_state = torch.tensor(
                    observation, dtype=torch.float32, device=device
                ).unsqueeze(0)

            agent.memory.push(state, action, next_state, reward)

            state = next_state

            agent.optimize_model()

            agent.update_target_net()

            if done:
                episode_rewards.append(total_reward)
                if (i_episode + 1) % 50 == 0:
                    print(
                        f"Episode {i_episode+1}/{settings.NUM_EPISODES}, Total Reward: {total_reward:.2f}"
                    )
                break

    print("Training complete.")
    agent.save_model()
    env.close()


if __name__ == "__main__":
    main()
