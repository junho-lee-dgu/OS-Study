# Lab 05 - System Programs, OS Structure, VM, and Boot

## 1. System Programs
- In this lab, I did not focus on classifying user commands into system program categories.
- Instead, I focused more on observing OS structure, virtualization, storage layout, and boot-related information from the running Linux environment.

## 2. Design and Implementation
- One important idea from the lecture is that OS design does not have a single universal answer.
- The OS must balance user goals such as convenience, reliability, safety, and speed with system goals such as maintainability, flexibility, correctness, and efficiency.
- I also reviewed the idea that policy means deciding *what* should be done, while mechanism means deciding *how* it is actually carried out.

## 3. OS Structure
- `lsmod` and `/proc/modules` showed that the Linux kernel is using loadable kernel modules.
- This means the OS is not just one indivisible block of code; some functionality is organized as modules.
- The outputs included modules such as `kvm_intel`, `kvm`, `irqbypass`, and others, which suggest that virtualization-related features are present in the running kernel.
- I observed that `lsmod` presents module information in a human-readable format, while `/proc/modules` shows a more raw kernel-facing representation of similar information.
- `ps -p 1 -o pid,comm,args` showed that PID 1 is `systemd` (`/sbin/init`), which means that the user-space initialization process is managed by systemd in my environment.

## 4. Virtual Machines
- My environment showed strong signs of virtualization.
- `/proc/cmdline` included WSL-specific parameters such as `WSL_ROOT_INIT=1` and `WSL_ENABLE_CRASH_DUMP=1`.
- The kernel command line also showed `console=hvc0`, which is consistent with a virtualized environment.
- This supports the idea that I am working inside a WSL2-based Linux environment rather than a traditional bare-metal Linux boot path.
- This lab helped me connect the lecture’s virtual machine concept with my real practice environment.

## 5. OS Generation and Machine-Specific Configuration
- `lsblk` showed the block devices visible to the running Linux system.
- I observed multiple disk-like devices, including a swap area (`[SWAP]`) and a mount point at `/mnt/wslg/distro`.
- This suggests that the OS is running with a storage configuration that is specific to the WSL2 environment.
- `cat /proc/filesystems` showed supported filesystem types such as `proc`, `sysfs`, `tmpfs`, `cgroup`, `ext3`, and `ext4`.
- Entries marked with `nodev` represent pseudo or virtual filesystems rather than regular disk-backed filesystems.
- This helped me understand that Linux exposes many kernel and system structures through filesystem-like interfaces.

## 6. System Boot
- `cat /proc/cmdline` showed the kernel boot parameters used to start this Linux environment.
- I observed parameters such as `initrd=\\initrd.img`, `nr_cpus=8`, and WSL-specific boot-related options.
- This gave me evidence that the kernel does not just “appear”; it is started with a specific boot configuration.
- `systemctl --version` showed that systemd is installed.
- `systemctl is-system-running` returned `running`, which means the system has successfully completed user-space initialization and is operating normally.
- Together with `ps -p 1`, this shows that the boot process has progressed far enough for `systemd` to become PID 1 and manage the running system.

## What I learned
- Kernel modules are an important part of modern OS structure.
- PID 1 is a key indicator of how the user-space side of boot is organized.
- My Linux practice environment is not just “Linux on hardware,” but a WSL2-based virtualized Linux environment.
- Filesystems in Linux include both regular disk filesystems and pseudo filesystems used to expose kernel and system information.
- Booting is not a single magic event; it involves kernel startup, boot parameters, and then initialization of user space.

## Questions
- How different would these observations look on a true bare-metal Linux installation?
- Which parts of the boot process are abstracted away by WSL2 and therefore not directly visible here?
- How do kernel modules, systemd, and boot parameters interact during a full Linux startup sequence?