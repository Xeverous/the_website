# setup

## clone the repository

```sh
git clone --recurse-submodules https://github.com/Xeverous/the_website.git
```

or, if you have already cloned:

```sh
git submodule update --init --recursive
```

## install required packages (these are for Ubuntu and derived distros)

CMake and Python development files are needed for C++ plugin code.

```sh
sudo apt install python3.9-dev python3-pip cmake
```

## create virtual environment (1 directory above `conf.py`)

```sh
sudo apt install python3.9-venv
python3.9 -m venv venv
```

## launch virtual environment

```sh
source ./venv/bin/activate
```

## when already in virtual environment

```sh
pip install -r requirements.txt
```

## build C++ plugin code

Part of website's build functionality is implemented in C++, which is compiled to a shared library object and loaded as a plugin by the Nikola build framework. Plugins also use additional tools such as [clangd](https://clangd.llvm.org). You can build the website without them, though it is discouraged as code snippets will be mostly non-functional (no highlight and other fancy features). It is only for the case where you have technical problems like Python being unable to load external modules or trouble installing LLVM tooling packages.

For Ubuntu and Debian distros, you can automatically install newest stable release of LLVM tools with the following (packages obtained this way can be multiple releases ahead of distro-supplied builds):

```sh
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh all
```

**ACH requires Boost only for CLI utility and tests (not needed for the website build).** The build options presented below are minimal defaults that require only a C++17 compiler. Everything else is provided in git submodules.

```sh
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

No installation step required. The Python plugin code is coded to load (import) from ACH build directory.

# working with the project

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
