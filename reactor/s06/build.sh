
###
 # @Author: Clark
 # @Email: haixuanwoTxh@gmail.com
 # @Date: 2024-09-20 16:01:22
 # @LastEditors: Clark
 # @LastEditTime: 2024-12-11 14:39:33
 # @Description: file content
###

mkdir build
cd build
# cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j16
# gdb ./test2 -ex "run"
