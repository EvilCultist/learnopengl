rm ./opengltut
mkdir build
cd build
clear
cmake ..
make
cd ..
__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./opengltut
