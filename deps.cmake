function(find_packages)
    find_package(unofficial-libharu CONFIG REQUIRED)
    find_package(imgui CONFIG REQUIRED)
    find_package(implot CONFIG REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
    find_package(Matplot++ CONFIG REQUIRED)
    find_package(Stb REQUIRED)

endfunction()

function(link_libs target)
    target_link_libraries(
    ${target}

    PRIVATE glfw
    PRIVATE glad::glad
    PRIVATE imgui::imgui
    PRIVATE implot::implot
    
    PRIVATE nlohmann_json::nlohmann_json
    
    PRIVATE unofficial::libharu::hpdf
    
    PRIVATE Matplot++::cimg
    PRIVATE Matplot++::matplot

    PRIVATE ${Stb_INCLUDE_DIR}
)
endfunction()

