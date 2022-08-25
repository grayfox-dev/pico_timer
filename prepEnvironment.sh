if [ ! -d pico-sdk ]; then
  echo "pico-sdk directory not found. Pulling from github..."
  git clone https://github.com/raspberrypi/pico-sdk.git
  if [ -d pico-sdk ]; then
    echo "pico-sdk retrieved. Pulling submodules."
    cd pico-sdk
    git pull
    git submodule update --init
  fi
else
  echo "pico-sdk directory found. Pulling & updating submodules"
  cd pico-sdk
  git pull
  git submodule update --init
fi
echo "Done."
