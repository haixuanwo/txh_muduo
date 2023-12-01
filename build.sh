
#!/bin/sh
###
 # @Author: Clark
 # @Email: haixuanwoTxh@gmail.com
 # @Date: 2023-11-29 11:00:17
 # @LastEditors: Clark
 # @LastEditTime: 2023-12-01 11:23:41
 # @Description: file content
###

set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-build}

mkdir -p $BUILD_DIR/ \
  && cd $BUILD_DIR/ \
  && cmake .. \
  && make $*
