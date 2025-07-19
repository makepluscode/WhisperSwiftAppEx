#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 간단한 transcribe 함수 (테스트용)
const char* transcribe(const char* audio_file_path, const char* model_path) {
    // 실제로는 여기서 whisper.cpp와 libsndfile을 사용하지만
    // 지금은 테스트용으로 간단한 메시지 반환
    return "Hello, this is a test transcription result from the audio file.";
} 