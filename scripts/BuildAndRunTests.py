
from os import remove
from pathlib import Path
from subprocess import Popen, PIPE, STDOUT
from sys import stdout
from time import sleep

# Constants
LOG_DELIMITER = "----------------------------------------------------------"

BUILD_DIR_NAME = "build"
UNIT_TESTS_EXE_NAME = "CrossPlatformSockets_tests.exe"

CROSS_PLATFORM_SOCKETS_PATH = Path(__file__).parent.parent
CROSS_PLATFORM_SOCKETS_BUILD_PATH = CROSS_PLATFORM_SOCKETS_PATH.joinpath(BUILD_DIR_NAME)
CROSS_PLATFORM_SOCKETS_TEST_EXE_PATH = Path(f"{CROSS_PLATFORM_SOCKETS_BUILD_PATH}/tests/Debug/{UNIT_TESTS_EXE_NAME}")

def stream_process_output(process):
   """
   Polls the running process for std output such that a running subprocess can have its output
   streamed to the console this Python script was run from
   """
   process_still_running = process.poll() is None
   for line in process.stdout:
      stdout.write(line.decode("utf-8")) # stdout does not use a new line like print
   return process_still_running

def exit_on_failure():
   """
   Function to call when this script fails, simply prints expected errors and ending strings
   """
   print("xx Exiting CrossPlatformSockets BuildAndRunTests")
   print(f"{LOG_DELIMITER}\n")
   exit()

# Start script
print(f"\n{LOG_DELIMITER}")
print("** Running CrossPlatformSockets BuildAndRunTests...")
print(f"-- Using paths:\n--> Parent path: {CROSS_PLATFORM_SOCKETS_PATH}\n--> Build path: {CROSS_PLATFORM_SOCKETS_BUILD_PATH}")

# Deal with build path
print("-- Checking if build path exists...")
build_path_exists = CROSS_PLATFORM_SOCKETS_BUILD_PATH.exists()
look_for_cmake_cache = build_path_exists

if build_path_exists:
   print("--> It does!")
else:
   print("--> Creating build dir...")
   CROSS_PLATFORM_SOCKETS_BUILD_PATH.mkdir()

# Deal with CMakeCache.txt
if look_for_cmake_cache:
   print("-- Checking if CMakeCache.txt exists")
   cmake_cache_path = CROSS_PLATFORM_SOCKETS_BUILD_PATH.joinpath("CMakeCache.txt")
   if not cmake_cache_path.exists():
      print("--> It does not!")
   else:
      print("--> Deleting CMakeCache.txt!")
      remove(cmake_cache_path)

# Run CMake and include unit tests
print("-- Running CMake on project...")
print(f"{LOG_DELIMITER}\n")

cmake_command_arguments = ["cmake", 
                           "-DBUILD_CROSS_PLATFORM_SOCKETS_UNIT_TESTS=ON", 
                           "-S",
                           CROSS_PLATFORM_SOCKETS_PATH,
                           "-B",
                           CROSS_PLATFORM_SOCKETS_BUILD_PATH]
process = Popen(cmake_command_arguments, stdout=PIPE, stderr=STDOUT)

# Stream output from sub process while it's still alive
while stream_process_output(process):
   sleep(0.1)

# Check results
print(f"\n{LOG_DELIMITER}")
print("** CrossPlatformSockets continuing...")
print("-- Checking outcome of prior CMake attempt")

return_code = process.poll()
if return_code is None or 0 != return_code:
   print("--> CMake command failed!")
   exit_on_failure()

print("--> CMake command succeeded!")

# Now run build the project
print("-- Building project...")
print(f"{LOG_DELIMITER}\n")

build_arguments = ["cmake", "--build", CROSS_PLATFORM_SOCKETS_BUILD_PATH]
process = Popen(build_arguments, stdout=PIPE, stderr=STDOUT)

# Stream output from sub process while it's still alive
while stream_process_output(process):
   sleep(0.1)

# Check results
print(f"\n{LOG_DELIMITER}")
print("** CrossPlatformSockets continuing...")
print("-- Checking outcome of build attempt")

return_code = process.poll()
if return_code is None or 0 != return_code:
   print("--> Build failed!")
   exit_on_failure()

print("--> Build succeeded!")

# Run unit tests
print("-- Running unit tests...")
print(f"{LOG_DELIMITER}\n")

process = Popen([CROSS_PLATFORM_SOCKETS_TEST_EXE_PATH], stdout=PIPE, stderr=STDOUT)

# Stream output from sub process while it's still alive
while stream_process_output(process):
   sleep(0.1)
