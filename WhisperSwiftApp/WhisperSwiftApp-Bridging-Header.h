#ifndef WhisperSwiftApp_Bridging_Header_h
#define WhisperSwiftApp_Bridging_Header_h

// 간단한 C 함수 선언만 포함
#ifdef __cplusplus
extern "C" {
#endif

// transcribe 함수 선언
const char* transcribe(const char* audio_file_path, const char* model_path);

#ifdef __cplusplus
}
#endif

#endif /* WhisperSwiftApp_Bridging_Header_h */ 