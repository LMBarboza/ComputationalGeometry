import random
from typing import List
from collections import namedtuple, deque
from typing import Unpack
import settings

Transition = namedtuple("Transition", ("state", "action", "next_state", "reward"))


class ReplayMemory:
    def __init__(self, capacity: int = settings.MEMORY_SIZE) -> None:
        self.memory = deque([], maxlen=capacity)

    def push(self, *args: Unpack[tuple]) -> None:
        self.memory.append(Transition(*args))

    def sample(self, batch_size: int = settings.BATCH_SIZE) -> List[Transition]:
        return random.sample(self.memory, batch_size)

    def __len__(self) -> int:
        return len(self.memory)
