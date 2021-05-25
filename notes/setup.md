# setup

## clone the repository

```sh
git clone https://github.com/Xeverous/the_website.git
```

## install required packages (these are for Ubuntu-derived distros)

```sh
sudo apt install python3.8-dev python3-pip cmake
pip3 install wheel
pip3 install setuptools
pip3 install virtualenv
```

## create virtual environment (1 directory above `conf.py`)

```sh
python3.8 -m virtualenv -p python3.8 venv
```

## launch virtual environment

```sh
source ./venv/bin/activate
```

## when already in virtual environment

```sh
pip install Nikola jinja2 aiohttp watchdog
```

## build C++ plugin code

```sh
git submodule update --init --recursive
cd website/external/arbitrary_code_highlighter
mkdir build
cd build
# this command MUST BE invoked while in a virtual environment
# you may want to:
# - enable/disable makefile verbosity
# - build ACH tests - requires boost 1.65+ headers
# - build ACH command-line executable - requires boost 1.65+ WITH program_options built
cmake .. -DACH_BUILD_TESTS=OFF -DACH_BUILD_EXECUTABLE_CLI=OFF -DACH_BUILD_PYTHON_MODULE=ON -DPYTHON_EXECUTABLE:FILEPATH=`which python` -DCMAKE_VERBOSE_MAKEFILE=ON
make -j
```

# working with the project

## launch virtual environment

```sh
source ./venv/bin/activate
```

## build the site (while inside virtual environment)

```sh
# cd to directory with conf.py
cd website

# now you can use any of the build methods

# incremental build
nikola build
# full build
nikola build -a
# launch server (blocking command)
nikola serve
# launch server with automatic incremental rebuilding (blocking command)
nikola auto
```

When Nikola server is launched, it will print an address that you can copy into the browser.

Note that changes to Python code may not be correctly applied in an incremental build.
