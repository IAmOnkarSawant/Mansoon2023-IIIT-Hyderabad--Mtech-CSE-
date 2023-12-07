import cv2
import pytesseract
import os
import json
import re


def extract_values(item):
    matches = re.findall(r'\b\d+[a-zA-Z%]+', item)
    result = {
        "Nutrients": None,
        "weight": None,
        "percentage": 0
    }

    if len(matches) >= 2:
        result["Nutrients"] = item.split(matches[0])[0].strip()
        # if item.endswith('g'):
        result["weight"] = matches[0]
        # if item.endswith('%'):
        result["percentage"] = float(matches[1].rstrip('%'))
    elif len(matches) == 1:
        if item.endswith('%'):
            result["Nutrients"] = item.split(matches[0])[0].strip()
            result["percentage"] = float(matches[0].rstrip('%'))
        elif item.endswith('g'):
            result["Nutrients"] = item.split(matches[0])[0].strip()
            result["weight"] = matches[0]

    return result

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
        pattern = r'\([^)]*\)'

        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        text = pytesseract.image_to_string(gray)
        mtext = re.sub(pattern, '', text)
        lines = mtext.split('\n')

        cleaned_list = [s.replace('\n', '') for s in lines]
        cleaned_list = [line.strip() for line in cleaned_list if line.strip()]

        input_list = cleaned_list
        result_list = []
        for item in input_list:
            result = extract_values(item)
            if any(result.values()):
                result_list.append(result)
        print(json.dumps(result_list))

    else:
        print("Failed to load the image.")
else:
    print(f"The image file '{image_path}' does not exist.")
