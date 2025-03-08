
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   FileDescriptorTest
    COMMAND  $<TARGET_FILE:FileDescriptorTest>
)

add_test(NAME   HashesSettingsTest
    COMMAND  $<TARGET_FILE:HashesSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(FileDescriptorTest       FileDescriptorTest.cpp)
add_executable(HashesSettingsTest       HashesSettingsTest.cpp)
