#include <whisper.h>
#include <sndfile.h>
#include <cstring>
#include <cstdlib>
#include <string>

extern "C" {

const char* transcribe(const char* audio_file_path, const char* model_path) {
    // 오디오 파일 열기
    SF_INFO sfinfo;
    sfinfo.format = 0;
    SNDFILE* sndfile = sf_open(audio_file_path, SFM_READ, &sfinfo);
    if (!sndfile) {
        return strdup("Error: Could not open audio file");
    }

    // 오디오 데이터 읽기
    int num_frames = sfinfo.frames;
    float* samples = new float[num_frames];
    sf_readf_float(sndfile, samples, num_frames);
    sf_close(sndfile);

    // Whisper 모델 로드
    whisper_context_params ctx_params = whisper_context_default_params();
    whisper_context* ctx = whisper_init_from_file_with_params(model_path, ctx_params);
    if (!ctx) {
        delete[] samples;
        return strdup("Error: Could not load model");
    }

    // Whisper 파라미터 설정
    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    params.print_progress = false;
    params.print_special = false;
    params.language = "auto";
    params.n_threads = 4;

    // 음성 인식 실행
    int result = whisper_full(ctx, params, samples, num_frames);
    delete[] samples;

    if (result != 0) {
        whisper_free(ctx);
        return strdup("Error: Transcription failed");
    }

    // 결과 텍스트 추출
    int num_segments = whisper_full_n_segments(ctx);
    std::string full_text;
    
    for (int i = 0; i < num_segments; ++i) {
        const char* segment_text = whisper_full_get_segment_text(ctx, i);
        full_text += segment_text;
        if (i < num_segments - 1) {
            full_text += " ";
        }
    }

    whisper_free(ctx);
    
    // 결과 반환 (메모리 해제는 Swift에서 처리)
    return strdup(full_text.c_str());
}

} // extern "C"