
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

add_executable       (md5-driver        MD5Driver.cpp)
target_link_libraries(md5-driver        ${project_target_prefix}MD5)

install(TARGETS         md5-driver
        DESTINATION     ${bintop_dir_name}/
)
