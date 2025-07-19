import Foundation

/// Swift에서 C++ Whisper 라이브러리를 사용하는 매니저 클래스
class WhisperManager: ObservableObject {
    @Published var transcriptionText: String = ""
    @Published var isTranscribing: Bool = false
    @Published var errorMessage: String = ""
    
    private let modelPath: String
    
    init() {
        // 번들에서 모델 파일 경로 가져오기
        guard let modelURL = Bundle.main.url(forResource: "ggml-tiny.en", withExtension: "bin") else {
            fatalError("Whisper model file not found in bundle")
        }
        self.modelPath = modelURL.path
    }
    
    /// WAV 파일을 텍스트로 변환
    func transcribeWAVFile(_ wavPath: String) {
        DispatchQueue.global(qos: .userInitiated).async {
            DispatchQueue.main.async {
                self.isTranscribing = true
                self.errorMessage = ""
            }
            
            // C++ 함수 호출
            transcribe(self.modelPath, wavPath)
            
            DispatchQueue.main.async {
                self.isTranscribing = false
                // 실제로는 C++ 함수에서 결과를 반환받아야 하지만,
                // 현재는 콘솔 출력만 하므로 임시로 메시지 표시
                self.transcriptionText = "Transcription completed. Check console for output."
            }
        }
    }
} 