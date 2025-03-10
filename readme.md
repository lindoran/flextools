# FlexTools

A collection of utilities to manage disk images and files for the FLEX09 operating system.

## FlexFloppy

Import and Export disk images, make new disk images, import files

`
$ ./flexfloppy 
Usage:
flexfloppy --in <disk.dsk> --cat
flexfloppy --in <disk.dsk> --extract <path>
flexfloppy --new --tracks <num_tracks> --sectors <num_sectors> [--label <label>] [--number <number>] --out <disk.dsk>
flexfloppy --in <disk.dsk> --add <filename>

`
