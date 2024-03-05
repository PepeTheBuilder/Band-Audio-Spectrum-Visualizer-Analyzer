import librosa
import numpy as np
import time
import bleak


# oneTime = False
# oneTime1 = False
def categorize_frequency_bands(y):
    if len(y) < 1:
        return None, None, None, None, None

    # Perform short-time Fourier transform
    D = librosa.stft(y)

    # Convert magnitude spectrogram to dB scale
    db_spec = librosa.amplitude_to_db(np.abs(D), ref=np.max)

    # Extract frequency bands
    bass = np.nan_to_num(np.mean(db_spec[0:100, :], axis=0))
    low_mid = np.nan_to_num(np.mean(db_spec[100:500, :], axis=0))
    mid = np.nan_to_num(np.mean(db_spec[500:1000, :], axis=0))
    mid_high = np.nan_to_num(np.mean(db_spec[1000:2000, :], axis=0))
    high = np.nan_to_num(np.mean(db_spec[2000:4000, :], axis=0))

    # Normalize and quantize to 3 bits each
    bass_quantized = quantize_to_3_bits(normalize(bass))
    low_mid_quantized = quantize_to_3_bits(normalize(low_mid))
    mid_quantized = quantize_to_3_bits(normalize(mid))
    mid_high_quantized = quantize_to_3_bits(normalize(mid_high))
    high_quantized = quantize_to_3_bits(normalize(high))

    # global oneTime
    # if not oneTime:
    #     print(bass_quantized, low_mid_quantized, mid_quantized, mid_high_quantized, high_quantized)
    #     oneTime = True
    return bass_quantized, low_mid_quantized, mid_quantized, mid_high_quantized, high_quantized


def normalize(data):
    range_data = np.max(data) - np.min(data)
    if range_data <= 0:
        return np.zeros_like(data)
    else:
        # Add check to ensure range_data is not zero or an invalid number before dividing
        return (data - np.min(data)) / range_data if range_data else np.zeros_like(data)


def quantize_to_3_bits(data):
    # return np.maximum(0,)
    step0 = np.clip(np.round(data * 7).astype(int), 0, 7)
    step1 = round(max(0, np.average(step0)))
    return min(7, step1)


# Example usage
file_path = "C:/Users/paulp/Downloads/bombs.mp3"
y, sr = librosa.load(file_path)

# Set the chunk duration in seconds
chunk_duration = 0.2

# Calculate the number of samples in each chunk
chunk_samples = int(chunk_duration * sr)

# Output file
output_file_path = "./output.txt"

feather_address = "33:48:AC:2F:A3:DB:1F:40"


async def send_frequency_bands_to_feather(bass, low_mid, mid, mid_high, high, device_address):
    try:
        async with bleak.BleakClient(device_address) as client:
            # Concatenate the frequency band data into a single string or format of your choice
            data_to_send = f"{bass},{low_mid},{mid},{mid_high},{high}"

            # Convert the data to bytes
            data_bytes = bytearray(data_to_send.encode())

            # Write the data bytes to the characteristic
            await client.write_gatt_char("0000ffe1-0000-1000-8000-00805f9b34fb", data_bytes)

            print("Frequency bands sent successfully.")

    except Exception as e:
        print(f"Error: {e}")



with open(output_file_path, 'w') as output_file:
    # Process audio in chunks
    for i in range(0, len(y), chunk_samples):
        chunk = y[i:i + chunk_samples]

        start_time = time.time()

        try:
            bass, low_mid, mid, mid_high, high = categorize_frequency_bands(chunk)
        except Exception as e:
            print(f"Error processing chunk {i // chunk_samples + 1}: {e}")
            continue

        output_file.write("{} ".format(bass))
        output_file.write("{} ".format(low_mid))
        output_file.write("{} ".format(mid))
        output_file.write("{} ".format(mid_high))
        output_file.write("{}\n".format(high))

        # send_frequency_bands_to_feather(bass, low_mid, mid, mid_high, high, feather_address)
        # print("Frequency bands sent successfully. chunk {}".format(i // chunk_samples + 1))
        # time.sleep(0.1)

    # Send the file to the Feather
    # loop = asyncio.get_event_loop()
    # loop.run_until_complete(send_file_to_feather(file_path, feather_address))
    # print("File sent successfully.")

# async def send_file_to_feather(file_path, device_address):
#     try:
#         async with bleak.BleakClient(device_address) as client:
#             # Read the content of the file
#             with open(file_path, 'rb') as file:
#                 file_content = file.read()
#
#             # Convert the file content to bytes
#             file_bytes = bytearray(file_content)
#
#             # Write the file bytes to the characteristic
#             await client.write_gatt_char("0000ffe1-0000-1000-8000-00805f9b34fb", file_bytes)
#
#             print("File sent successfully.")
#     except Exception as e:
#         print(f"Error: {e}")
