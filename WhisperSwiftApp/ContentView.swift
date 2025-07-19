//
//  ContentView.swift
//  WhisperSwiftApp
//
//  Created by makepluscode on 7/19/25.
//

import SwiftUI

struct ContentView: View {
    @State private var transcribedText: String = ""
    @State private var isTranscribing: Bool = false
    
    var body: some View {
        VStack(spacing: 30) {
            // 아이콘과 타이틀
            VStack(spacing: 20) {
                Image(systemName: "waveform")
                    .font(.system(size: 60))
                    .foregroundColor(.blue)
                
                Text("Whisper Speech-to-Text")
                    .font(.title)
                    .fontWeight(.bold)
            }
            
            // 결과 텍스트 영역
            ScrollView {
                VStack(alignment: .leading, spacing: 10) {
                    if isTranscribing {
                        HStack {
                            ProgressView()
                                .scaleEffect(0.8)
                            Text("Transcribing...")
                                .foregroundColor(.gray)
                        }
                    } else if !transcribedText.isEmpty {
                        Text("Transcription Result:")
                            .font(.headline)
                            .foregroundColor(.blue)
                        
                        Text(transcribedText)
                            .font(.body)
                            .padding()
                            .background(Color.gray.opacity(0.1))
                            .cornerRadius(8)
                    } else {
                        Text("Press the button below to transcribe test.wav")
                            .font(.body)
                            .foregroundColor(.gray)
                            .multilineTextAlignment(.center)
                    }
                }
                .padding()
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            
            // 버튼
            Button(action: {
                transcribeAudio()
            }) {
                HStack {
                    Image(systemName: "play.fill")
                        .foregroundColor(.white)
                    Text("Transcribe test.wav")
                        .foregroundColor(.white)
                        .fontWeight(.semibold)
                }
                .padding()
                .frame(maxWidth: .infinity)
                .background(Color.blue)
                .cornerRadius(10)
            }
            .disabled(isTranscribing)
            .padding(.horizontal)
        }
        .padding()
    }
    
    private func transcribeAudio() {
        print("🎤 Transcribe button pressed!")
        isTranscribing = true
        transcribedText = ""
        
        // 백그라운드에서 transcribe 실행
        DispatchQueue.global(qos: .userInitiated).async {
            print("🔄 Starting transcription in background...")
            
            // 임시로 테스트 메시지 사용 (C 함수 연결 전까지)
            let result = "Hello, this is a test transcription result from the audio file."
            print("✅ Transcription completed: \(result)")
            
            // UI 업데이트는 메인 스레드에서
            DispatchQueue.main.async {
                print("📱 Updating UI with result...")
                isTranscribing = false
                transcribedText = result
                print("🎉 UI updated successfully!")
            }
        }
    }
}

#Preview {
    ContentView()
}
