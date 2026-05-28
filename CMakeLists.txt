cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME flight_controller)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Fix linker script path (toolchain file assumes root, script lives in STM32HAL/)
string(REPLACE
    "${CMAKE_SOURCE_DIR}/STM32F411XX_FLASH.ld"
    "${CMAKE_SOURCE_DIR}/STM32HAL/STM32F411XX_FLASH.ld"
    CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}"
)

# Enable CMake support for ASM, C, and C++ languages
enable_language(C CXX ASM)
set(CMAKE_CXX_STANDARD 17)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(STM32HAL/cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)



file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    src/drivers/*.cpp
    src/wrappers/*.cpp
    src/logging/*.cpp
)


# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    src/fc_main.cpp
    ${SRC_FILES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    src
    src/drivers
    src/wrappers
    src/logging
    STM32HAL/Middlewares/Third_Party/FreeRTOS/Source/include
    STM32HAL/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    STM32HAL/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    STM32HAL/Core/Inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
