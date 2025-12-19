## Mounting additional hard disk (VMWare WS).

1. Right-click a VM -> Properties -> Add... (within Devices tab) -> Hard disk/Type/Choise/Size/Place/Done

2. Linux commands: 
```bash
df -h (shows mounted drives, FS, size, used and free space, mounting point
lsblk (shows connected drives, name, size, mounting point
```
3. Tools FDISK and PARTED
```bash
parted -l
parted /dev/sdb
```
(parted) mklabel gpt (Partition Table)
(parted) mkpart extradrive ext4 1MB 10GB (name, filesystem, size from to)
(parted) print

4. Format disk
```bash
mkfs -t ext4 /dev/sdb1
```
5. Mounting
```bash
mkdir /home/extra                    # (create a folder to wherever you like which you gonna use for mounting new hard drive)
mount /dev/sdb1 /home/extra/         # (mount you sdb1 to folder "extra")
vim /etc/fstab                       # (edit fstab so that this mout be permanent)
```
add line: `/dev/sdb1 (or better UUID) /home/extra ext4 defaults 0 0`



