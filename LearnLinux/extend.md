## How to extend disk zise on Rocky

### Check
```bash
df -h   #checking whole fs
df -h / # checking /
---
Filesystem      Size  Used Avail Use%
/dev/mapper/rl-root   15G   15G     0 100%
---
df -i #checking inode outage
du -xh / --max-depth=1 | sort -h    #top catalogs on /
du -xh /var --max-depth=1 | sort -h #top catalogs in /var

journalctl --disk-usage       # check the size of the system journal
journalctl --vacuum-size=200M # cleanup thejournal
journalctl --vacuum-time=7d   # cleanup by time

du -sh /var/log/audit           # check if auditd overloadeddisk space
systemctl stop auditd           # temprarily...
rm -f /var/log/audit/audit.log* # remove...
systemctl start auditd          # and start auditd

dnf clean all                 # cleanup dnf cache

lsblk
---
nvme0n1 259:0 0 200G 0 disk 
├─nvme0n1p1 259:1 0 1G 0 part /boot 
└─nvme0n1p2 259:2 0 199G 0 part 
  ├─rl-root 253:0 0 70G 0 lvm / 
  ├─rl-swap 253:1 0 7.9G 0 lvm [SWAP] 
  └─rl-home 253:2 0 121.1G 0 lvm /home
---
vgs
---
VG #PV #LV #SN Attr VSize VFree 
rl 1 3 0 wz--n- <199.00g 0
---
lvs
 LV VG Attr LSize Pool Origin Data% Meta% Move Log
Cpy%Sync Convert
 home rl -wi-ao---- <121.14g
 root rl -wi-ao---- 70.00g
 swap rl -wi-ao---- <7.86g
---
lvextend -r -l +100%FREE /dev/mapper/rl-root

```


### Method 1
Redude `/home` and extend `/root`
```bash
umount /home
lvreduce -L 60G /dev/rl/home
lvextend -r -L +61G /dev/rl/root
mount /home
```
> [!IMPORTANT]
> target can be busy <br>
> `lvreduce` can damage data
> if /home is XSF - `forget abour this option`

Check FS type:
```bash
findmnt -o TARGET,SOURCE,FSTYPE /home
df -T /home
```


### Method 2
Move Docker to `/home`
```bash
docker system df

systemctl stop docker

mkdir -p /home/docker
rsync -aHAX /var/lib/docker/ /home/docker/

mv /var/lib/docker /var/lib/docker.bak
ln -s /home/docker /var/lib/docker

systemctl start docker
rm -rf /var/lib/docker.bak

docker info | grep "Docker Root Dir"

```
> [!IMPORTANT]
> ❌`docker system prune -a --volumes` will remove all stopped containers, images, volumes<br>
> BE CAREFUL <br>
> ✔ A good solution <br>
> ✔ k8s-friendly <br>
> ✔ homelab standard <br>


### Method 3 (best)
Enlarge VM disk <br>

```bash
lsblk
---
nvme0n1   200G
└─nvme0n1p2 199G
```
VMware Workstation → VM → Settings → Hard Disk → Expand


```bash
lsblk
---
nvme0n1   300G
└─nvme0n1p2 199G
---
dnf install -y cloud-utils-growpart
growpart /dev/nvme0n1 2
lsblk
---
nvme0n1   300G
└─nvme0n1p2 299G
---

pvresize /dev/nvme0n1p2
pvs
vgs
lvextend -r -l +100%FREE /dev/rl/root

pvs
---
  PV             VG Fmt  Attr PSize    PFree
  /dev/nvme0n1p2 rl lvm2 a--  <299.00g    0

vgs
---
  VG #PV #LV #SN Attr   VSize    VFree
  rl   1   3   0 wz--n- <299.00g    0
lvs
---
  LV   VG Attr       LSize    Pool Origin Data%  Meta%  Move Log Cpy%Sync Convert
  home rl -wi-ao---- <121.14g
  root rl -wi-ao----  170.00g
  swap rl -wi-ao----   <7.86g
df -h /
---
Filesystem           Size  Used Avail Use% Mounted on
/dev/mapper/rl-root  170G   71G  100G  42% /

```


