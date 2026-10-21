cmake_minimum_required(VERSION 3.22)

project(scop LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opciones de compilación
option(USE_SYSTEM_SDK "Usar Vulkan y SDL instalados en el sistema" OFF)
option(USE_SDL2 "Usar SDL2 en lugar de SDL3" OFF)

add_executable(scop
    src/main.cpp
    src/Vect3.cpp
    src/Obj.cpp
    src/parser.cpp
    src/utils.cpp
    src/vulkan_init.cpp
)

# Advertencias del compilador
target_compile_options(scop PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -Wno-missing-braces
)

# --------------------------------------------------
# Vulkan
# --------------------------------------------------

if(USE_SYSTEM_SDK)
    # Si VULKAN_SDK está definido, utilizar ese SDK.
    if(DEFINED ENV{VULKAN_SDK} AND NOT "$ENV{VULKAN_SDK}" STREQUAL "")
        set(VULKAN_DIR "$ENV{VULKAN_SDK}")
    else()
        # Vulkan instalado en el sistema.
        find_package(Vulkan REQUIRED)
    endif()
else()
    # SDK utilizado en el entorno de /goinfre.
    set(VULKAN_DIR
        "/goinfre/jrollon-/scop_vulkan/1.3.296.0/x86_64"
    )

    target_include_directories(scop SYSTEM PRIVATE
        "${VULKAN_DIR}/include"
    )

    target_link_directories(scop PRIVATE
        "${VULKAN_DIR}/lib"
    )

    set_property(TARGET scop APPEND PROPERTY BUILD_RPATH
        "${VULKAN_DIR}/lib"
    )
endif()

if(USE_SYSTEM_SDK AND DEFINED VULKAN_DIR)
    target_include_directories(scop SYSTEM PRIVATE
        "${VULKAN_DIR}/include"
    )

    target_link_directories(scop PRIVATE
        "${VULKAN_DIR}/lib"
    )

    set_property(TARGET scop APPEND PROPERTY BUILD_RPATH
        "${VULKAN_DIR}/lib"
    )
endif()

# --------------------------------------------------
# GLM
# --------------------------------------------------

if(NOT USE_SYSTEM_SDK)
    target_include_directories(scop SYSTEM PRIVATE
        "/goinfre/jrollon-/scop_vulkan/sources/glm"
    )
elseif(EXISTS "/usr/include/glm")
    # GLM instalado en /usr/include no necesita -I.
elseif(EXISTS "/usr/local/include/glm")
    target_include_directories(scop SYSTEM PRIVATE
        "/usr/local/include"
    )
endif()

# --------------------------------------------------
# SDL
# --------------------------------------------------

if(USE_SDL2)
    find_package(SDL2 REQUIRED)

    target_compile_definitions(scop PRIVATE USING_SDL2)

    target_link_libraries(scop PRIVATE SDL2::SDL2)
else()
    if(USE_SYSTEM_SDK)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)

        target_link_libraries(scop PRIVATE PkgConfig::SDL3)
    else()
        set(SDL3_DIR
            "/goinfre/jrollon-/scop_vulkan/deps_local"
        )

        target_include_directories(scop SYSTEM PRIVATE
            "${SDL3_DIR}/include"
        )

        target_link_directories(scop PRIVATE
            "${SDL3_DIR}/lib"
        )

        target_link_libraries(scop PRIVATE SDL3)

        set_property(TARGET scop APPEND PROPERTY BUILD_RPATH
            "${SDL3_DIR}/lib"
        )
    endif()
endif()

# --------------------------------------------------
# Enlazado de Vulkan y shaderc
# --------------------------------------------------

target_link_libraries(scop PRIVATE shaderc_combined)

if(USE_SYSTEM_SDK AND NOT DEFINED VULKAN_DIR)
    target_link_libraries(scop PRIVATE Vulkan::Vulkan)
else()
    target_link_libraries(scop PRIVATE vulkan)
endif()
