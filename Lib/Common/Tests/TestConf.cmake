
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   HashesSettingsTest
    COMMAND  $<TARGET_FILE:HashesSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(HashesSettingsTest       HashesSettingsTest.cpp)
