# libwhisper

A C++ speech-to-text engine wrapper for OpenAI Whisper models, designed for integration with Swift/iOS/macOS apps and other C++ projects.

## Structure

- `include/` : Public C/C++ headers (e.g., `whisper_wrapper.h`)
- `src/`     : Implementation source files (e.g., `whisper_wrapper.cpp`)
- `resources/` : Model and test audio files (e.g., `ggml-tiny.en.bin`, `test.wav`)
- `tests/`   : GoogleTest-based unit tests
- `CMakeLists.txt` : CMake build configuration

## Build & Test

```sh
cd libwhisper
mkdir -p build && cd build
cmake ..
make -j
./test_transcribe
```

## Features
- C++/C API for Whisper model inference
- Easy integration with Swift/iOS/macOS via static library
- GoogleTest-based unit testing

## License
MIT (or project license) 