include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

function(fetch_glfw)
    CPMAddPackage(
            NAME GLFW
            GITHUB_REPOSITORY glfw/glfw
            GIT_TAG 3.3.9
            OPTIONS
                "GLFW_BUILD_TESTS OFF"
                "GLFW_BUILD_EXAMPLES OFF"
                "GLFW_BULID_DOCS OFF"
    )
endfunction()



function(create_imgui_library)

    # todo: assert glfw is available

    set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui CACHE PATH "Path to ImGui source directory")

    add_library(
            imgui
            ${IMGUI_DIR}/imgui.cpp
            ${IMGUI_DIR}/imgui_demo.cpp
            ${IMGUI_DIR}/imgui_draw.cpp
            ${IMGUI_DIR}/imgui_tables.cpp
            ${IMGUI_DIR}/imgui_widgets.cpp
            ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
            ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    )

    target_link_libraries(imgui PRIVATE glfw)

    target_include_directories(imgui
            PUBLIC
            ${IMGUI_DIR}
            ${IMGUI_DIR}/backends
    )


endfunction()


function(create_glad_library)

    set(GLAD_ROOT ${CMAKE_SOURCE_DIR}/vendor/glad CACHE PATH "Path to GLAD source directory")

    add_library(
            glad
            STATIC
            ${GLAD_ROOT}/include/glad/glad.h
            ${GLAD_ROOT}/include/KHR/khrplatform.h
            ${GLAD_ROOT}/src/glad.c

    )

    target_include_directories(glad PUBLIC ${GLAD_ROOT}/include)


endfunction()

function(create_implot_library)

    set(IMPLOT_ROOT ${CMAKE_SOURCE_DIR}/vendor/implot CACHE PATH "Path to IMPLOT source directory")

    add_library(
        implot
        STATIC
        ${IMPLOT_ROOT}/implot.cpp
        ${IMPLOT_ROOT}/implot_items.cpp
    )
    
    target_include_directories(implot PUBLIC ${IMPLOT_ROOT})

    target_link_libraries(implot PRIVATE imgui)

endfunction()

function(fetch_json)
    CPMAddPackage(
            NAME NLOHMANN_JSON
            GITHUB_REPOSITORY nlohmann/json
            VERSION 3.11.3
            OPTIONS
                "JSON_BuildTests OFF"
                "JSON_CI OFF"
    )

endfunction()

function(fetch_matplot)
    add_subdirectory(vendor/matplot)
endfunction()

