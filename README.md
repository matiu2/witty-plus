Installation on ubuntu Natty:

# Install packages
sudo apt-get update
sudo apt-get install libwt-dev libwtdbopostgres-dev postgresql cmake build-essential cmake-curses-gui
sudo apt-get build-dep libwt-dev libwtdbopostgres-dev

# Get wt trunk
cd
mkdir projects
cd projects
git clone http://www.webtoolkit.eu/git/wt.git
cd wt
mkdir build
cd build
cmake ..
# optional configure with: ccmake ..
make -j 4


# Get the source
git clone git://github.com/matiu2/witty-plus.git

# Build it
cd witty-plus/base-app
mkdir build
cd build
cmake ..
# optional configure with: ccmake ..
make -j 2

# set up the DB
sudo su postgres
createuser my_app
createdb my_app
psql my_app
grant all on database my_app to my_app;
alter user my_app password 'my_app';
\q
exit

# set up the data
./setup

# run the app
sh run.sh

# look at it
/usr/bin/chromium-browser http://localhost:8000
