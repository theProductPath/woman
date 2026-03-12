# WOMAN - WoMAN Pages
# Docker image for web-based terminal access via ttyd
#
# Build:  docker build -t woman .
# Run:    docker run -p 7681:7681 woman
# Access: http://localhost:7681

FROM ubuntu:22.04

# Install build tools, ncurses, and ttyd
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

# Create app directory
WORKDIR /app

# Copy source files
COPY src/ ./src/

# Build WOMAN
WORKDIR /app/src
RUN make clean && make

# Create a wrapper script that launches woman cleanly
RUN cat > /app/run-woman.sh << 'SCRIPT'
#!/bin/bash
# Set terminal to 80x24 for authentic experience
export TERM=xterm-256color
stty rows 24 cols 80 2>/dev/null

cd /app/src
exec ./woman
SCRIPT
RUN chmod +x /app/run-woman.sh

# ttyd serves on port 7681 by default
EXPOSE 7681

# Launch ttyd with WOMAN
# --writable: allow keyboard input
# --max-clients 0: unlimited concurrent users
# --title-format: browser tab title
CMD ["ttyd", \
     "--writable", \
     "--max-clients", "0", \
     "--title-format", "WoMAN - Unix Command Browser (1989)", \
     "--client-option", "fontSize=15", \
     "--client-option", "fontFamily=Courier New,monospace", \
     "/app/run-woman.sh"]
