# FlexTools

A collection of utilities to manage disk images and files for the FLEX09 operating system.

## FlexFloppy

Import and Export disk images, make new disk images, import files


    $ flexfloppy 
    Usage:
    flexfloppy --in <disk.dsk> --cat
    flexfloppy --in <disk.dsk> --extract <path>
    flexfloppy --new --tracks <num_tracks> --sectors <num_sectors> [--label <label>] [--number <number>] --out <disk.dsk>
    flexfloppy --in <disk.dsk> --add <filename>

Command example : 

    $ flexfloppy --in TSCFLX09.DSK --cat
    Disk has 35 tracks, 10 sectors.

    Volume label  : FLEX-SWT
    Volume number : 6809
    Creation date : 3/10/80
    Tracks        : 35
    Free sectors  : 161
    Max track     : 34
    Max sector    : 10

    FILENAME EXT  SECTORS   DATE     TRACK,SECTOR
    ---------------------------------------------
    ERRORS   SYS        9   03/10/80        01,01
    FLEX     SYS       25   03/10/80        01,10
    PRINT    SYS        1   03/10/80        04,05
    CAT      CMD        3   03/10/80        04,06
    DELETE   CMD        2   03/10/80        05,04
    P        CMD        1   03/10/80        05,06
    LIST     CMD        3   03/10/80        05,07
    ASN      CMD        1   03/10/80        05,10
    RENAME   CMD        1   03/10/80        06,01
    APPEND   CMD        3   03/10/80        06,02
    BUILD    CMD        1   03/10/80        06,05
    EXEC     CMD        1   03/10/80        06,06
    NEWDISK  CMD        6   03/10/80        06,07
    SAVE     CMD        2   03/10/80        07,03
    TTYSET   CMD        2   03/10/80        07,05
    O        CMD        2   03/10/80        07,07
    LINK     CMD        1   03/10/80        07,09
    JUMP     CMD        1   03/10/80        07,10
    DATE     CMD        2   03/10/80        08,01
    PRINT    CMD        2   03/10/80        08,03
    PROT     CMD        1   03/10/80        08,05
    QCHECK   CMD        4   03/10/80        08,06
    VERIFY   CMD        1   03/10/80        08,10
    VERSION  CMD        1   03/10/80        09,01
    XOUT     CMD        2   03/10/80        09,02
    I        CMD        1   03/10/80        09,04
    EDIT     CMD       28   03/10/80        09,05
    ASMB     CMD       48   03/10/80        12,03
    SAVE     LOW        2   03/10/80        17,01
    FLEX     COR       22   03/10/80        17,03
    ---------------------------------------------
    USED SECTORS      179
