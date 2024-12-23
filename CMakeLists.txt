cmake_minimum_required(VERSION 3.16)
project(PlatformerGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#===============Link libraries=========================
include_directories(
    ${CMAKE_SOURCE_DIR}/externals/SDL2-2.30.10/include
    ${CMAKE_SOURCE_DIR}/externals/SDL2_image-2.8.2/include
    ${CMAKE_SOURCE_DIR}/externals/SDL2_mixer-2.8.0/include
    ${CMAKE_SOURCE_DIR}/externals/SDL2_ttf-2.22.0/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/externals/SDL2-2.30.10/lib/x64
    ${CMAKE_SOURCE_DIR}/externals/SDL2_image-2.8.2/lib/x64
    ${CMAKE_SOURCE_DIR}/externals/SDL2_mixer-2.8.0/lib/x64
    ${CMAKE_SOURCE_DIR}/externals/SDL2_ttf-2.22.0/lib/x64
)
#======================================================


#=====================Includes=========================
#Get Engine's sources
aux_source_directory(sources SRC)
aux_source_directory(sources/Core SRC_CORE)
aux_source_directory(sources/Audio SRC_AUDIO)
aux_source_directory(sources/Entities SRC_ENTITIES)
aux_source_directory(sources/Render SRC_RENDER)
aux_source_directory(sources/Inputs SRC_INPUTS)
aux_source_directory(sources/Physics SRC_PHYSICS)
aux_source_directory(sources/Utils SRC_UTILS)

set(SOURCES
    ${SRC}
    ${SRC_CORE}
    ${SRC_AUDIO}
    ${SRC_ENTITIES}
    ${SRC_RENDER}
    ${SRC_INPUTS}
    ${SRC_PHYSICS}
    ${SRC_UTILS}
    )

#include sources root
include_directories(sources)
#======================================================


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
        "${CMAKE_SOURCE_DIR}/externals/SDL2-2.30.10/lib/x64/SDL2.dll"
        "${CMAKE_SOURCE_DIR}/externals/SDL2_image-2.8.2/lib/x64/SDL2_image.dll"
        "${CMAKE_SOURCE_DIR}/externals/SDL2_mixer-2.8.0/lib/x64/SDL2_mixer.dll"
        "${CMAKE_SOURCE_DIR}/externals/SDL2_ttf-2.22.0/lib/x64/SDL2_ttf.dll"
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

# Copier le dossier config dans le dossier de sortie
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/config"
    "${CMAKE_BINARY_DIR}/config"
)