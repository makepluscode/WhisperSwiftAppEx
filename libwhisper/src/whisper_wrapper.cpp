#include "whisper_wrapper.h"
#include "whisper.h"
#include <vector>
#include <iostream>
#include <sndfile.h>

// Loads a WAV file and converts it to mono float32 PCM
static bool load_wav(const char *filename, std::vector<float> &pcmf32) {
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile) {
        std::cerr << "Failed to open WAV file: " << filename << std::endl;
        return false;
    }
    std::vector<float> tmp(sfinfo.frames * sfinfo.channels);
    sf_readf_float(sndfile, tmp.data(), sfinfo.frames);
    sf_close(sndfile);
    // Convert to mono
    pcmf32.resize(sfinfo.frames);
    for (int i = 0; i < sfinfo.frames; ++i) {
        float sum = 0.0f;
        for (int c = 0; c < sfinfo.channels; ++c) {
            sum += tmp[i * sfinfo.channels + c];
        }
        pcmf32[i] = sum / sfinfo.channels;
    }
    return true;
}

extern "C" {
void transcribe(const char *model_path, const char *wav_path) {
    struct whisper_context_params cparams = whisper_context_default_params();
    struct whisper_context *ctx = whisper_init_from_file_with_params(model_path, cparams);
    if (!ctx) {
        std::cerr << "모델 로딩 실패\n";
        return;
    }
    std::vector<float> pcmf32;
    if (!load_wav(wav_path, pcmf32)) {
        std::cerr << "wav 로딩 실패\n";
        whisper_free(ctx);
        return;
    }
    struct whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    whisper_full(ctx, params, pcmf32.data(), pcmf32.size());
    int n_segments = whisper_full_n_segments(ctx);
    for (int i = 0; i < n_segments; ++i) {
        const char *text = whisper_full_get_segment_text(ctx, i);
        std::cout << text << std::endl;
    }
    whisper_free(ctx);
}
} // extern "C"