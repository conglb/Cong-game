cmake_minimum_required(VERSION 3.15)

project(CongGame CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
set(SRC
        main.cpp
        Game.cpp
        Window.cpp
        painter.cpp
        Graphics.cpp
)

add_executable(cong-game ${SRC})

# Try pkg-config first (common on macOS/Linux)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_SDL2 QUIET sdl2)
pkg_check_modules(PC_SDL2_MIXER QUIET SDL2_mixer)
pkg_check_modules(PC_SDL2_IMAGE QUIET SDL2_image)

if (PC_SDL2_FOUND)
    target_include_directories(cong-game PRIVATE
            ${PC_SDL2_INCLUDE_DIRS}
            ${PC_SDL2_MIXER_INCLUDE_DIRS}
            ${PC_SDL2_IMAGE_INCLUDE_DIRS}
    )
    target_link_directories(cong-game PRIVATE
            ${PC_SDL2_LIBRARY_DIRS}
            ${PC_SDL2_MIXER_LIBRARY_DIRS}
            ${PC_SDL2_IMAGE_LIBRARY_DIRS}
    )
    target_link_libraries(cong-game PRIVATE
            ${PC_SDL2_LIBRARIES}
            ${PC_SDL2_MIXER_LIBRARIES}
            ${PC_SDL2_IMAGE_LIBRARIES}
    )
else()
    # Fallback: CMake packages (works if SDL2 provides config files)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_image REQUIRED)

    # Use variables if imported targets are not available
    if (TARGET SDL2::SDL2)
        target_link_libraries(cong-game PRIVATE SDL2::SDL2)
    else()
        target_include_directories(cong-game PRIVATE ${SDL2_INCLUDE_DIRS})
        target_link_libraries(cong-game PRIVATE ${SDL2_LIBRARIES})
    endIf()

    if (TARGET SDL2_mixer::SDL2_mixer)
        target_link_libraries(cong-game PRIVATE SDL2_mixer::SDL2_mixer)
    else()
        target_include_directories(cong-game PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
        target_link_libraries(cong-game PRIVATE ${SDL2_MIXER_LIBRARIES})
    endif()

    if (TARGET SDL2_image::SDL2_image)
        target_link_libraries(cong-game PRIVATE SDL2_image::SDL2_image)
    else()
        target_include_directories(cong-game PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
        target_link_libraries(cong-game PRIVATE ${SDL2_IMAGE_LIBRARIES})
    endif()
endif()

# Include project headers
target_include_directories(cong-game PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# Copy runtime assets next to the executable
function(copy_dir_to_target tgt dir_name)
    if(EXISTS "${CMAKE_SOURCE_DIR}/${dir_name}")
        add_custom_command(TARGET ${tgt} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/${dir_name}"
                "$<TARGET_FILE_DIR:${tgt}>/${dir_name}"
                COMMENT "Copying ${dir_name} to output directory"
        )
    endif()
endfunction()

copy_dir_to_target(cong-game image)
copy_dir_to_target(cong-game sound)

# Output directory
set_target_properties(cong-game PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")