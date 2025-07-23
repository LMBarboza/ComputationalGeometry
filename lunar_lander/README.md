# Lunar Lander (Deep Q-Learning)

This directory contains an implementation of a **Deep Q-Learning (DQN)** agent for [Gymnasium Lunar Lander](https://gymnasium.farama.org/environments/box2d/lunar_lander/) environment.

## Structure
- **`run.py`** – Runs the trained agent in the environment.
- **`train.py`** – Trains the agent using Deep Q-Learning.
- **`modules/`** – Contains the core components used for the agent, such as the neural network, replay buffer, and training utilities.
- **`lunar_lander.pth`** – Pre-trained PyTorch model weights, trained for **600 episodes** using an **epsilon-greedy** exploration strategy with diminishing epsilon.

## Running

Dependencies are specified in the `pyproject.toml` file.  
Scripts can be run either inside a virtual environment or using [uv](https://github.com/astral-sh/uv).

### Option 1: Using a Virtual Environment
1. Install dependencies

2. Run scripts:

   ```bash
   python run.py
   python train.py
   ```

### Option 2: Using uv

Run scripts directly:

```bash
uv run run.py
uv run train.py
```

### Notes

* Video showing the trained agent interacting with the environment is available at `videos`
*  Training parameters are specified in `modules/settings.py`. Training episodes, batch size, learning rate, and epsilon schedule are all adjustable.
