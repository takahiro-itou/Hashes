
##
##    List of Tests.
##

extra_tests             =
TESTS                   =  \
        MD5Test                 \
        ${extra_tests}

##
##    Test Configurations.
##

target_testee_library       +=  -lhsMD5

dist_noinst_data_files      +=
dist_noinst_header_files    +=
extra_test_drivers          +=
library_test_drivers        +=
source_test_drivers         +=

##
##    Compile and Link Options.
##

test_cppflags_common        +=
test_ldflags_common         +=

##
##    Test Programs.
##

MD5Test_SOURCES             =  MD5Test.cpp

