Requirements.

gcc

make

Note. gcc alone is not sufficient to build multi-file C projects.

Build instructions.

Open a terminal.

Verify gcc is installed.

gcc --version


Verify make is installed.

make --version


If make is missing, install it.

Ubuntu or Debian:

sudo apt update
sudo apt install make


Fedora:

sudo dnf install make


Arch:

sudo pacman -S make


Navigate to the project directory.

cd path/to/BankManagmentSystemcolored


Build the project.

make


This will compile all source files in src/ and generate the executable:

bank_system


Run the program.

./bank_system


Clean build files.

make clean


Notes.

Re-running make recompiles only modified files.

Header dependencies are handled automatically.

No IDE is required.

The same Makefile works on Linux and MinGW.
