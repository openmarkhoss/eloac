#!/bin/sh
# ============================================
# E-L-O-A-C v0.1 Installer
# Ephemeral Local Offline AI Chat
# ============================================

set -e

echo "======================================"
echo " E-L-O-A-C v0.1 INSTALLER"
echo " Ephemeral Local Offline AI Chat"
echo "======================================"
echo

# 1. Ensure build tools exist
echo "[1/4] Checking build tools..."
if ! command -v gcc >/dev/null 2>&1; then
    echo "Installing build-essential..."
    sudo apt update
    sudo apt install -y build-essential
else
    echo "Build tools already present."
fi

# 2. Create install directory
echo
echo "[2/4] Creating local directory..."
INSTALL_DIR="$HOME/eloac"
mkdir -p "$INSTALL_DIR"
cd "$INSTALL_DIR"

# 3. Download source
echo
echo "[3/4] Downloading E-L-O-A-C source..."
curl -fsSL https://raw.githubusercontent.com/YOUR_USERNAME/YOUR_REPO/main/eloac.c -o eloac.c

# 4. Compile
echo
echo "[4/4] Compiling..."
gcc eloac.c -o eloac -lm

echo
echo "======================================"
echo " Installation complete"
echo "======================================"
echo
echo "Run with:"
echo "  cd ~/eloac && ./eloac"
echo
echo "For best effect:"
echo "  - fullscreen terminal"
echo "  - black background"
echo "  - green text"
echo
echo "E-L-O-A-C lives only while running."
echo
