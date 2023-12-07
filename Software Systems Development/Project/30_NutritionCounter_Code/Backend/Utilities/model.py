import cv2
import pytesseract
import os

folder_path = os.path.abspath('uploads')  # Use an absolute path

file_name = ''
if os.path.exists(folder_path):
    files = os.listdir(folder_path)
    if len(files) == 1 and os.path.isfile(os.path.join(folder_path, files[0])):
        file_name = files[0]
    else:
        if len(files) == 0:
            print(f"No files found in the folder.")
        else:
            print(f"There are multiple files in the folder. Unable to determine the single file.")
else:
    print(f"The folder '{folder_path}' does not exist.")

# Construct the full path to the image file
image_path = os.path.join(folder_path, file_name)

if os.path.isfile(image_path):
    image = cv2.imread(image_path)
    if image is not None:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        text = pytesseract.image_to_string(gray)
        lines = text.split(',')
        cleaned_list = [s.replace('\n', '') for s in lines]
        cleaned_list = [line.strip() for line in cleaned_list if line.strip()]
        formatted_text = '\n'.join(cleaned_list)
        print(formatted_text)

    else:
        print("Failed to load the image.")
else:
    print(f"The image file '{image_path}' does not exist.")
