import Foundation

@_silgen_name("transcribe")
func transcribe(_ modelPath: UnsafePointer<CChar>, _ wavPath: UnsafePointer<CChar>)

let modelPath = "./Resources/ggml-tiny.en.bin"
let wavPath = "./Resources/test.wav"

modelPath.withCString { mPath in
    wavPath.withCString { wPath in
        transcribe(mPath, wPath)
    }
}