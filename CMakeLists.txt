# WhisperSwiftApp/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(WhisperSwiftApp)

set(CMAKE_CXX_STANDARD 17)

# whisper.cpp 추가
add_subdirectory(/Users/bginess/Workspace/whisper.cpp whisper_lib)

# wrapper 빌드
add_library(whisper_wrapper SHARED
    Sources/WhisperWrapper.cpp
)

target_include_directories(whisper_wrapper PRIVATE
    /Users/bginess/Workspace/whisper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources
)

target_link_libraries(whisper_wrapper whisper /opt/homebrew/opt/libsndfile/lib/libsndfile.dylib)

# Add Homebrew libsndfile paths
include_directories(/opt/homebrew/opt/libsndfile/include)
link_directories(/opt/homebrew/opt/libsndfile/lib)

# If you want to build a Swift executable, add the following:
# Enable Swift language support
# (Uncomment the next line if using CMake >= 3.15 and want to build Swift)
# enable_language(Swift)

# Add executable for main.swift (if you want to build and run it)
# add_executable(WhisperSwiftApp main.swift)
# target_link_libraries(WhisperSwiftApp whisper_wrapper)

# GoogleTest integration for unit testing
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} /opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Test target for transcribe
add_executable(test_transcribe Tests/test_transcribe.cpp)
target_include_directories(test_transcribe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
target_link_libraries(test_transcribe whisper_wrapper ${GTEST_LIBRARIES} pthread)