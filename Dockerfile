# WOMAN - WoMAN Pages
# Top-level Dockerfile for Railway deployment
# Railway auto-detects this file and builds from it

FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        libncurses5-dev \
        man-db \
        manpages \
        manpages-dev \
        ttyd \
        less \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY src/ ./src/

WORKDIR /app/src
RUN make clean && make

RUN cat > /app/run-woman.sh << 'SCRIPT'
#!/bin/bash
export TERM=xterm-256color
stty rows 24 cols 80 2>/dev/null
cd /app/src
exec ./woman
SCRIPT
RUN chmod +x /app/run-woman.sh

# Railway sets PORT env var; ttyd needs to listen on it
EXPOSE ${PORT:-7681}

CMD ttyd \
    --port ${PORT:-7681} \
    --writable \
    --max-clients 0 \
    --title-format "WoMAN - Unix Command Browser (1989)" \
    --client-option fontSize=15 \
    --client-option "fontFamily=Courier New,monospace" \
    /app/run-woman.sh
