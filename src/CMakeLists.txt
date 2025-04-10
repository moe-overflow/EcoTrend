file(
        GLOB_RECURSE SOURCE_FILES
        "*.cpp"
        "*.hpp"
)

add_executable(
        ${TARGET_NAME}
        ${SOURCE_FILES}
)

include(${CMAKE_SOURCE_DIR}/deps.cmake)
find_packages()
link_libs(${TARGET_NAME})

