
##
##    バイナリのビルドとインストール。
##

##
##    List of Directories.
##

module_dir_name     =  Binary
SUBDIRS             =  .

include  $(top_srcdir)/.M4/BuildCommon/DirList.inc

##
##    List of Source and Header Files.
##

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS          =  \
        -I${inctop_source_dir}
AM_CFLAGS               =
AM_CXXFLAGS             =
AM_LDFLAGS              =  -L${libtop_binary_dir}

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        md5-driver

dist_noinst_DATA        =  \
        CMakeLists.txt

##
##    Build Executables.
##

md5_driver_SOURCES      =  MD5Driver.cpp
md5_driver_LDADD        =  -lhsMD5

