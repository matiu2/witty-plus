Installation on ubuntu Natty:

# Install packages
sudo apt-get update
sudo apt-get install postgresql libwt-dev libwtdbopostgres-dev cmake build-essential cmake-curses-gui
sudo apt-get build-dep libwt-dev libwtdbopostgres-dev

# Get wt trunk
cd
mkdir projects
cd projects
git clone http://www.webtoolkit.eu/git/wt.git

# Get witty-plus trunk
git clone git://github.com/matiu2/witty-plus.git

# Patch witty
cd wt
patch -p1 < ../witty-plus/wt.patch

# Build witty
mkdir build
cd build
cmake ..
# optionaly configure with: ccmake ..
make
sudo make install

# Build witty-plus
cd ../../witty-plus/base-app
mkdir build
cd build
cmake ..
# optionaly configure with: ccmake ..
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
