#!/bin/bash

DISKS=original_disks
DST=lflex_disks
LFLEX=target_lflex
WORK=work


function base_disk() {

    disk_file=$DST/$1
    label=$2
    number=$3

    flexfloppy --new --tracks 80 --sectors 20 --label $label --number $number --out $disk_file
    flexfloppy --in $disk_file --add $LFLEX/FLEX.SYS
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/CAT.CMD
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/COPY.CMD
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/DELETE.CMD
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/RENAME.CMD
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/EDIT.CMD
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/ASN.CMD
    flexfloppy --in $disk_file --add $WORK/TSCFLX09/LIST.CMD
    flexfloppy --in $disk_file --bootsector $LFLEX/bootsector.bin
    flexfloppy --in $disk_file --setboot FLEX.SYS
}

function copy_content() {
    dest=$1
    src=$2

    for file in $WORK/$src/*
    do
        flexfloppy --in $DST/$dest --add $file
    done
}

# Uncompress disks
for disk in $DISKS/*.DSK
do
    dest="$WORK/$(basename $disk .DSK)"
    mkdir -p $dest
    flexfloppy --in $disk --extract $dest
done

# TSC FLEX09
flexfloppy --new --tracks 80 --sectors 20 --label TSCFLEX09 --number 1 --out $DST/tscflex09.lflex.img
flexfloppy --in $DST/tscflex09.lflex.img --add $LFLEX/FLEX.SYS
flexfloppy --in $DST/tscflex09.lflex.img --bootsector $LFLEX/bootsector.bin
flexfloppy --in $DST/tscflex09.lflex.img --setboot FLEX.SYS

for file in $WORK/TSCFLX09/*
do
    filename="$(basename $file)"
    echo $file
    if [[ "$filename" != "FLEX.SYS" ]]
    then
        flexfloppy --in $DST/tscflex09.lflex.img --add $file
    fi 
done


# BASIC
base_disk basic.lflex.img XBASIC_2 2
copy_content basic.lflex.img XBASIC_2

# EFORTH
base_disk eforth.lflex.img EFORTH 3
copy_content eforth.lflex.img EFORTH

# INTROL C
base_disk introlc.lflex.img INTROLC 4
copy_content introlc.lflex.img INTROLC

# FORTRAN
base_disk fortran.lflex.img TSC_F77 5
copy_content fortran.lflex.img TSC_F77

# DYNASTAR
base_disk dynastar.lflex.img DYNASTAR 6
copy_content dynastar.lflex.img DYNSTAR