# Use a lightweight Linux image with GCC
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy your C files into the container
COPY . /app

# Default command: open a bash shell
CMD ["/bin/bash"]
