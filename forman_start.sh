#cd /tmp/debug
"/usr/bin/cmake" --build . --target all
#cd ~/jdragon
foreman start -f Procfile.dev
