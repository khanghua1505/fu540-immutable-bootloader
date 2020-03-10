#!/bin/bash

set -e

# Relevant partition type codes
BBL=2E54B353-1271-4842-806F-E436D6AF6985
LINUX=0FC63DAF-8483-4772-8E79-3D69D8477DE4
FSBL=5B193300-FC78-40CD-8002-E86C45580B47

MKE2FS=mke2fs
DISK=$1
echo "Operating on $DISK"
test -b $DISK

echo "$DISK exists, paritioning..."

# Configure the partitions on the disk.
# NOTE: The block ranges given here are for the 8GB card we are using
#       You may wish to use different partition sizes.
sgdisk --clear \
       --new=1:2048:67583  --change-name=1:bootloader --typecode=1:$BBL   \
       --new=2:264192:     --change-name=2:root       --typecode=2:$LINUX \
       --new=3:67584:69631 --change-name=3:siv-fsbl   --typecode=3:$FSBL \
       $DISK
sleep 1

PART_BBL=$DISK"1"
PART_LINUX=$DISK"2"
PART_FSBL=$DISK"3"

echo "COPYING BBL to $PART_BBL"
test -b $PART_BBL
dd if=bbl.bin of=$PART_BBL bs=4096
echo "Copy done"

echo "COPYING FSBL to $PART_FSBL"
test -b $PART_FSBL
$MKE2FS -t ext3 $PART_FSBL
dd if=fsbl.bin of=$PART_FSBL bs=1024
echo "Copy done"
