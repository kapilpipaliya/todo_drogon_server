rsync -avz --progress . kapil@95.216.152.135:/home/kapil/jdrogon

cd /home/kapili3/k/scert
rsync -avz --progress . kapil@95.216.152.135:/srv/http/react/.well-known/acme-challenge

sudo pacman -S cmake
sudo pacman -S qt
sudo pacman -S libpqxx  --- not working
sudo pacman -S boost boost-libs

https://github.com/trizen/trizen#installation
git clone https://aur.archlinux.org/trizen.git
cd trizen
makepkg -si

sudo pacman -S postgresql-libs

sudo pacman -R mariadb mariadb-libs mariadb-clients
mariadb must not installed otherwise it requires all libs of it.

I installed libpqxx from source and it works:
https://github.com/jtv/libpqxx
include_directories(/usr/local/include)

https://github.com/an-tao/drogon/wiki/installation
mkdir build
cd build
cmake ..
make && sudo make install

sudo pacman -S jsoncpp range-v3

# regular task
ssh kapil@95.216.152.135
cd /home/kapil/jdrogon/build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./jdragon

# 