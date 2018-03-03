#!/usr/bin/python3
from IOT.core import *
import argparse
import os

if __name__ == '__main__':
    parse = argparse.ArgumentParser()
    parse.add_argument("file_input", help="the file that you want optimize")
    parse.add_argument("file_output", help="the file that we create")
    args = parse.parse_args()
    exe = Executable(args.file_input)
    exe.save_at(args.file_output)
