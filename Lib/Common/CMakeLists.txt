
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(module_title        "Common")

Include (${common_cmake_dir}/BuildCommon/ConfigModule.cmake)
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(library_source_files
        AppOpts.cpp
        FileDescriptor.cpp
        SampleDocument.cpp
)

set(inclib_header_files
        ${inclib_source_dir}/AppOpts.h
        ${inclib_source_dir}/FileDescriptor.h
        ${inclib_source_dir}/HashesSettings.h
        ${inclib_source_dir}/HashesTypes.h
        ${inclib_source_dir}/SampleDocument.h
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${common_cmake_dir}/BuildCommon/BuildLib.cmake)
Include (${common_cmake_dir}/BuildCommon/Install.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

Add_SubDirectory (Tests)
