
import sys
import os
import string
from ctypes import windll

if len(sys.argv) != 2:
    sys.exit(-1)

def find_drive():
    drive = None
    bitmask = windll.kernel32.GetLogicalDrives()
    for letter in string.uppercase:
        if (bitmask & 1) and os.path.isfile(letter + ':\\firmware.bin'):
            drive = letter
            break
        bitmask >>= 1

    return drive

drive = find_drive()
if drive:
    print('find %s' % drive)
    os.system('copy /Y ' + sys.argv[1] + ' ' + drive + ':\\firmware.bin')
