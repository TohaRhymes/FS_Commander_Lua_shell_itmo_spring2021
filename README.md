## NTFS file system reader: lua-script
__System Software lab 2__

[REPORT](https://github.com/TohaRhymes/FS_Commander_Lua_shell_itmo_spring2021/blob/master/%D0%A1%D0%9F%D0%9E_%D0%BB%D0%B0%D0%B12_%D0%A7%D0%B0%D0%BD%D0%B3%D0%B0%D0%BB%D0%B8%D0%B4%D0%B8_P33122.docx.pdf)


### Information
* `launch.lua` - lua-script, that takes c library and use it to read NTFS.
* `lib_ntfs.so` - c library for lua script


### ```list```-example

To run program in list mode use `list` key.

Input:
```
$ sudo lua launch.lua list
```
Output:
```
System partition:
name		size	type
/dev/loop7	55 MiB	squashfs
/dev/loop23	65 MiB	squashfs
/dev/loop13	32 MiB	squashfs
/dev/loop3	61 MiB	squashfs
/dev/loop4	77 MiB	squashfs
/dev/loop5	55 MiB	squashfs
/dev/loop6	815 MiB	squashfs
/dev/nvme0n1p5	55 GiB	ext4
/dev/loop0	614 MiB	squashfs
/dev/loop1	98 MiB	squashfs
/dev/loop2	76 MiB	squashfs
/dev/loop21	503 MiB	squashfs
/dev/loop20	240 MiB	squashfs
/dev/loop19	816 MiB	squashfs
/dev/nvme0n1p6	7 GiB	swap
/dev/nvme0n1p1	260 MiB	vfat
/dev/nvme0n1p3	261 GiB	BitLocker
/dev/nvme0n1p4	530 MiB	ntfs
/dev/nvme0n1p7	151 GiB	ext4
/dev/loop17	64 MiB	squashfs
/dev/loop16	295 MiB	squashfs
/dev/loop15	162 MiB	squashfs
/dev/loop14	503 MiB	squashfs
/dev/loop18	613 MiB	squashfs
/dev/loop22	99 MiB	squashfs
/dev/loop12	301 MiB	squashfs
/dev/nvme0n1p2	16 MiB	
/dev/loop9	32 MiB	squashfs
/dev/loop8	218 MiB	squashfs
/dev/loop11	51 MiB	squashfs
   
```

### ```commander``` launch

To run it in shell mode use `commander` key and specify drive or deviceDescriptor.

```
$ sudo lua launch.lua commander
```
