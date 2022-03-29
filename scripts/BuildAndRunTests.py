
from os import remove
from pathlib import Path

# Constants
LOG_DELIMITER = "----------------------------------------------------------"

BUILD_DIR_NAME = "build"
CROSS_PLATFORM_SOCKETS_PATH = Path(__file__).parent.parent
CROSS_PLATFORM_SOCKETS_BUILD_PATH = CROSS_PLATFORM_SOCKETS_PATH.joinpath(BUILD_DIR_NAME)

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

