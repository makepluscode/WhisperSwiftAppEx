cmake_minimum_required(VERSION 3.10)
project(libwhisper)

set(CMAKE_CXX_STANDARD 17)

# === whisper.cpp 라이브러리 추가 ===
add_subdirectory(/Users/bginess/Workspace/whisper.cpp whisper_lib)

# === 통합 정적 라이브러리 (모든 의존성 포함) ===
add_library(whisper_wrapper_complete STATIC
    src/whisper_wrapper.cpp
)
target_include_directories(whisper_wrapper_complete PRIVATE
    /Users/bginess/Workspace/whisper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# iOS 빌드시 모든 의존성을 정적 라이브러리로 링크
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    target_link_libraries(whisper_wrapper_complete 
        whisper 
        /opt/homebrew/opt/libsndfile/lib/libsndfile.a
    )
    include_directories(/opt/homebrew/opt/libsndfile/include)
    link_directories(/opt/homebrew/opt/libsndfile/lib)
else()
    target_link_libraries(whisper_wrapper_complete 
        whisper 
        /opt/homebrew/opt/libsndfile/lib/libsndfile.dylib
    )
    include_directories(/opt/homebrew/opt/libsndfile/include)
    link_directories(/opt/homebrew/opt/libsndfile/lib)
endif()

# === whisper_wrapper 라이브러리 (기존) ===
add_library(whisper_wrapper SHARED
    src/whisper_wrapper.cpp
)
target_include_directories(whisper_wrapper PRIVATE
    /Users/bginess/Workspace/whisper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(whisper_wrapper whisper /opt/homebrew/opt/libsndfile/lib/libsndfile.dylib)
include_directories(/opt/homebrew/opt/libsndfile/include)
link_directories(/opt/homebrew/opt/libsndfile/lib)

# === whisper_wrapper 정적 라이브러리 (iOS/Swift 연동용) ===
add_library(whisper_wrapper_static STATIC
    src/whisper_wrapper.cpp
)
target_include_directories(whisper_wrapper_static PRIVATE
    /Users/bginess/Workspace/whisper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# iOS 빌드시 libsndfile 정적 라이브러리 링크
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    # iOS용 libsndfile 정적 라이브러리 경로 (Homebrew 설치)
    target_link_libraries(whisper_wrapper_static whisper /opt/homebrew/opt/libsndfile/lib/libsndfile.a)
    include_directories(/opt/homebrew/opt/libsndfile/include)
    link_directories(/opt/homebrew/opt/libsndfile/lib)
else()
    # macOS용 동적 라이브러리 링크
    target_link_libraries(whisper_wrapper_static whisper /opt/homebrew/opt/libsndfile/lib/libsndfile.dylib)
    include_directories(/opt/homebrew/opt/libsndfile/include)
    link_directories(/opt/homebrew/opt/libsndfile/lib)
endif()

# === 통합 정적 라이브러리 (모든 의존성 포함) ===
add_library(whisper_wrapper_universal STATIC
    src/whisper_wrapper.cpp
)
target_include_directories(whisper_wrapper_universal PRIVATE
    /Users/bginess/Workspace/whisper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# iOS 빌드시 모든 의존성을 정적 라이브러리로 링크
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    target_link_libraries(whisper_wrapper_universal 
        whisper 
        /opt/homebrew/opt/libsndfile/lib/libsndfile.a
        /opt/homebrew/opt/libsndfile/lib/libsndfile.a
    )
    include_directories(/opt/homebrew/opt/libsndfile/include)
    link_directories(/opt/homebrew/opt/libsndfile/lib)
else()
    target_link_libraries(whisper_wrapper_universal 
        whisper 
        /opt/homebrew/opt/libsndfile/lib/libsndfile.dylib
    )
    include_directories(/opt/homebrew/opt/libsndfile/include)
    link_directories(/opt/homebrew/opt/libsndfile/lib)
endif()

# === GoogleTest 통합 (iOS 빌드시 주석 처리) ===
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS} /opt/homebrew/include)
# link_directories(/opt/homebrew/lib)

# === 테스트 타겟 (iOS 빌드시 주석 처리) ===
# add_executable(test_transcribe tests/test_transcribe.cpp)
# target_include_directories(test_transcribe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(test_transcribe whisper_wrapper ${GTEST_LIBRARIES} pthread)

# === Swift 실행 파일 (필요시) ===
# enable_language(Swift)
# add_executable(WhisperSwiftApp main.swift)
# target_link_libraries(WhisperSwiftApp whisper_wrapper)