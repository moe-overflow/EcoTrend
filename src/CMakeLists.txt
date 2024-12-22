file(
        GLOB_RECURSE SOURCE_FILES
        "*.cpp"
        "*.hpp"
)

add_executable(
        Ecotrend
        ${SOURCE_FILES}
)

target_link_libraries(
    Ecotrend

    PUBLIC imgui
    PUBLIC glfw
    PUBLIC glad
    PUBLIC implot
    PRIVATE nlohmann_json::nlohmann_json
)

