cmake_minimum_required(VERSION 3.15)
project(SDL2_Platformer)

# Spécifiez le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajout des fichiers source
file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(include)

# Chemin d'accès vers les ressources
set(RC_PATH ${CMAKE_SOURCE_DIR}/ressources)

# Ajouter le chemin vers les librairies
set(SDL2_PATH ${CMAKE_SOURCE_DIR}/external/SDL2) # SDL2
set(SDL2_TTF_PATH ${CMAKE_SOURCE_DIR}/external/SDL2_ttf) # SDL2_ttf

# Inclure SDL2
include_directories(${SDL2_PATH}/include)
link_directories(${SDL2_PATH}/lib/x64)

# Inclure SDL2_ttf
include_directories(${SDL2_TTF_PATH}/include)
link_directories(${SDL2_TTF_PATH}/lib/x64)

# Ajouter l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Lier SDL2
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf)

# Copier le dossier ressources vers le dossier de sortie
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RC_PATH}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/ressources)

# Copier les DLL dans le dossier de sortie
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_PATH}/lib/x64/SDL2.dll
        ${SDL2_TTF_PATH}/lib/x64/SDL2_ttf.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
