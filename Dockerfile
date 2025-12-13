FROM ubuntu:24.04

WORKDIR /opt

RUN apt update \
    && apt install -y --no-install-recommends make g++ libreadline-dev libfuse3-dev fuse3 python3 python3-pip dpkg-dev \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .

RUN pip3 install --break-system-packages -r requirements.txt \
  && find / -name "*.pyc" -exec rm -f {} \; 2>/dev/null || true \
  && rm -rf /root/.cache/

COPY . .

CMD ["./check.sh"]
