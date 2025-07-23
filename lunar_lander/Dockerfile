FROM python:3.12-slim
COPY --from=ghcr.io/astral-sh/uv:latest /uv /uvx /bin/

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONUNBUFFERED=1
ENV UV_SYSTEM_PYTHON=true


RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    python3-dev \
    pkg-config \
    swig \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY lunar_lander/pyproject.toml ./pyproject.toml
COPY lunar_lander/uv.lock ./uv.lock
COPY lunar_lander/README.md ./README.md


RUN uv sync

COPY lunar_lander/modules/ ./modules/
COPY lunar_lander/train.py ./train.py
COPY lunar_lander/run.py ./run.py
COPY lunar_lander/lunar_lander.pth ./lunar_lander.pth

CMD ["uv", "run", "train.py"]
