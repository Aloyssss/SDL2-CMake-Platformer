# Définir la version minimale de CMake et le nom du projet
cmake_minimum_required(VERSION 3.16)
project(PlatformerGame CXX)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter les répertoires include et src
include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Ajouter les chemins d'inclusion
include_directories(
    ${CMAKE_SOURCE_DIR}/external/SDL2-2.30.10/include
    ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.8.2/include
    ${CMAKE_SOURCE_DIR}/external/SDL2_mixer-2.8.0/include
    ${CMAKE_SOURCE_DIR}/external/SDL2_ttf-2.22.0/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/external/SDL2-2.30.10/lib/x64
    ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.8.2/lib/x64
    ${CMAKE_SOURCE_DIR}/external/SDL2_mixer-2.8.0/lib/x64
    ${CMAKE_SOURCE_DIR}/external/SDL2_ttf-2.22.0/lib/x64
)

# Ajouter l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Lier SDL2 et ses extensions à l'exécutable
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2
    SDL2main
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

# Copier les DLL nécessaires
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/external/SDL2-2.30.10/lib/x64/SDL2.dll"
        "${CMAKE_SOURCE_DIR}/external/SDL2_image-2.8.2/lib/x64/SDL2_image.dll"
        "${CMAKE_SOURCE_DIR}/external/SDL2_mixer-2.8.0/lib/x64/SDL2_mixer.dll"
        "${CMAKE_SOURCE_DIR}/external/SDL2_ttf-2.22.0/lib/x64/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()


# Copier le dossier ressources dans le dossier de sortie
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/ressources"
    "${CMAKE_BINARY_DIR}/ressources"
)