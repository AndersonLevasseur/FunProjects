import os
import whisper
import glob

def transcribe_files(file_list, output_dir):
    # Load the Whisper model
    model = whisper.load_model("base")

    # Ensure the output directory exists
    os.makedirs(output_dir, exist_ok=True)

    for file_path in file_list:
        try:
            # Transcribe the audio file
            result = model.transcribe(file_path)
            transcription = result["text"]

            # Generate output file path
            base_name = os.path.basename(file_path)
            output_file = os.path.join(output_dir, f"{os.path.splitext(base_name)[0]}.txt")

            # Write transcription to a text file
            with open(output_file, "w", encoding="utf-8") as f:
                f.write(transcription)

            print(f"Transcription for '{file_path}' saved to '{output_file}'")
        except Exception as e:
            print(f"Error transcribing '{file_path}': {e}")

if __name__ == "__main__":
    # Find all .m4a files in the current directory
    files_to_transcribe = glob.glob("*.m4a")
    output_directory = "transcriptions"

    transcribe_files(files_to_transcribe, output_directory)