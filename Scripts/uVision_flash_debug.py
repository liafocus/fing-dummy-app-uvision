import subprocess
import os
import time

current_directory = os.getcwd()
bat_file_path = os.path.join(current_directory, "Scripts/uVision_flash_debug.bat")
UV4_EXE= "C:/Keil_v5/UV4/UV4.exe"
AXF_FILE= os.path.join(current_directory,"Objects/fing-dummy-app-uvision.axf")

def keil_flash():
    # Construct the command list
    cmd = [UV4_EXE, "-f", AXF_FILE, "-j0"]

    # Execute the command
    subprocess.run(cmd, shell=True)

if __name__ == "__main__":
    # Flash the application (-b) in headless mode (-j0)
    keil_flash()
    
    # Start measuring time
    start_time = time.time()
    subprocess.run(bat_file_path, shell=True)

    # Calculate debug time
    elapsed_time = time.time() - start_time

    # Print the debug time
    print(f"Debug time: {elapsed_time} seconds")

