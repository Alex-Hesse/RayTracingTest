FROM rocm/dev-ubuntu-22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    #unzip \
    #python3-dev \
    #python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . .

CMD ["bash"]