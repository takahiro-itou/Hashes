
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   SampleDocumentTest
    COMMAND  $<TARGET_FILE:SampleDocumentTest>
)

add_test(NAME   HashesSettingsTest
    COMMAND  $<TARGET_FILE:HashesSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(SampleDocumentTest       SampleDocumentTest.cpp)
add_executable(HashesSettingsTest       HashesSettingsTest.cpp)
