import pyautogui
import time
import keyboard
import subprocess


def type_lines_from_file(file_path_var):
    with open(file_path_var, 'r') as file:
        lines = file.readlines()

    for line in lines:
        pyautogui.typewrite(line)
        time.sleep(0.2
                   )
        pyautogui.click(button='left')
        # time.sleep(1.5)
        # Check if Ctrl+C is pressed to stop the script
        if keyboard.is_pressed('ctrl + c'):
            print("Ctrl+C pressed. Stopping script...")
            return


if __name__ == '__main__':
    file_path = 'C:/Users/paulp/PycharmProjects/pythonProject1/output.txt'  # Replace with your actual file path
    print("Start in 5 seconds...")
    time.sleep(1)
    print("4 seconds")
    time.sleep(1)
    print("3 seconds")
    time.sleep(1)
    subprocess.run(['start', 'cmd', '/min', '/k', 'start', "C:/Users/paulp/Downloads/bombs.mp3"], shell=True)
    print("2 seconds")
    time.sleep(1)
    print("1 seconds")
    time.sleep(1)
    print("NOW!")
    type_lines_from_file(file_path)
