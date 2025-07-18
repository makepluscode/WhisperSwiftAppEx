#include <gtest/gtest.h>
#include "WhisperWrapper.h"
#include <filesystem>

TEST(WhisperTranscribeTest, RunsWithoutCrash) {
    const char *model_path = "../Resources/ggml-tiny.en.bin";
    const char *wav_path = "../Resources/test.wav";
    // 파일 존재 여부 확인
    ASSERT_TRUE(std::filesystem::exists(model_path));
    ASSERT_TRUE(std::filesystem::exists(wav_path));
    // transcribe 함수가 예외 없이 실행되는지만 확인
    ASSERT_NO_THROW({ transcribe(model_path, wav_path); });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 