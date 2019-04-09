#!/usr/bin/python
import sys
import fnmatch
import os

def teste():
    folder = 'c:/boost'
    pattern = '*.*'

    for root, dirs, files in os.walk(folder):
        #for filename in fnmatch.filter(files, pattern):
        for filename in files:
            print(os.path.join(root, filename))

def main():
    # print command line arguments
    for arg in sys.argv[1:]:
        print(arg)

if __name__ == "__main__":
    main()


