# ESP-IDF SMART-WATCH

## RUN DOCKER COMMAND
 - `docker run --rm -v ${PWD}:/project -w /project -it espressif/idf:release-v4.4`

## ESPRESSIF COMMANDS
 - Run Monitor: `C:\Users\jaime\.espressif\python_env\idf5.0_py3.8_env\Scripts\python.exe C:\Users\jaime\esp\esp-idf\tools\idf_monitor.py -p COM3 -b 115200 --toolchain-prefix xtensa-esp32-elf- --target esp32 d:\docker-esp32\project\build\smart-watch.elf`