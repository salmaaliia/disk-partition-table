#include <stdio.h>
#include <string.h>
#include "PartitionsTypes.h"

Partition types[] = {
    {0x00, "Unused"},                              // 0x00
    {0x01, "FAT12"},                               // 0x01
    {0x02, "XENIX root"},                          // 0x02
    {0x03, "XENIX usr"},                           // 0x03
    {0x04, "FAT16 (<32M)"},                        // 0x04
    {0x05, "Extended Partition (CHS)"},            // 0x05
    {0x06, "FAT16"},                               // 0x06
    {0x07, "HPFS/NTFS/exFAT"},                     // 0x07
    {0x08, "AIX"},                                 // 0x08
    {0x09, "AIX bootable"},                        // 0x09
    {0x0A, "OS/2 Boot Manager"},                   // 0x0A
    {0x0B, "W95 FAT32"},                          // 0x0B
    {0x0C, "W95 FAT32 (LBA)"},                    // 0x0C
    {0x0E, "W95 FAT16 (LBA)"},                    // 0x0E
    {0x0F, "W95 Extended (LBA)"},                  // 0x0F
    {0x10, "OPUS"},                                // 0x10
    {0x11, "Hidden FAT12"},                        // 0x11
    {0x12, "Compaq diagnostics"},                  // 0x12
    {0x14, "Hidden FAT16 (<32M)"},                 // 0x14
    {0x16, "Hidden FAT16"},                        // 0x16
    {0x17, "Hidden HPFS/NTFS"},                    // 0x17
    {0x18, "AST SmartSleep"},                      // 0x18
    {0x1B, "Hidden W95 FAT32"},                    // 0x1B
    {0x1C, "Hidden W95 FAT32 (LBA)"},              // 0x1C
    {0x1E, "Hidden W95 FAT16 (LBA)"},              // 0x1E
    {0x24, "NEC DOS"},                             // 0x24
    {0x27, "Hidden NTFS WinRE"},                   // 0x27
    {0x39, "Plan 9"},                              // 0x39
    {0x3C, "PartitionMagic recovery"},             // 0x3C
    {0x40, "Venus partition"},                     // 0x40
    {0x41, "PPC PReP Boot"},                       // 0x41
    {0x42, "SFS"},                                 // 0x42
    {0x4D, "QNX4.x"},                              // 0x4D
    {0x4E, "QNX4.x 2nd part"},                    // 0x4E
    {0x4F, "QNX4.x 3rd part"},                    // 0x4F
    {0x50, "OnTrack DM"},                          // 0x50
    {0x51, "OnTrack DM6 Aux1"},                    // 0x51
    {0x52, "CP/M"},                                // 0x52
    {0x53, "OnTrack DM6 Aux3"},                    // 0x53
    {0x54, "OnTrackDM6"},                          // 0x54
    {0x55, "EZ-Drive"},                            // 0x55
    {0x56, "Golden Bow"},                          // 0x56
    {0x57, "DR DOS/secured"},                      // 0x57
    {0x58, "AOS"},                                 // 0x58
    {0x5C, "Priam EDisk"},                         // 0x5C
    {0x61, "SpeedStor"},                           // 0x61
    {0x63, "GNU HURD or SysV"},                    // 0x63
    {0x64, "Novell Netware 286"},                  // 0x64
    {0x65, "Novell Netware 386"},                  // 0x65
    {0x66, "Novell Storage Services (NSS)"},       // 0x66
    {0x67, "Novell Partition"},                    // 0x67
    {0x70, "DiskSecure Multi-Boot"},               // 0x70
    {0x75, "PC/IX"},                               // 0x75
    {0x7E, "Reserved"},                            // 0x7E
    {0x7F, "XOSL FS"},                             // 0x7F
    {0x80, "Minix <1.4a"},                         // 0x80
    {0x81, "Minix >=1.4b"},                        // 0x81
    {0x82, "Linux swap"},                          // 0x82
    {0x83, "Linux"},                               // 0x83
    {0x84, "Hidden Linux"},                        // 0x84
    {0x85, "Linux extended"},                      // 0x85
    {0x86, "NTFS volume set"},                     // 0x86
    {0x87, "NTFS volume set"},                     // 0x87
    {0x88, "Linux plaintext"},                     // 0x88
    {0x89, "BSD/OS"},                              // 0x89
    {0xA5, "FreeBSD"},                            // 0xA5
    {0xA6, "OpenBSD"},                            // 0xA6
    {0xA7, "NeXTSTEP"},                           // 0xA7
    {0xA8, "Darwin UFS"},                         // 0xA8
    {0xA9, "NetBSD"},                             // 0xA9
    {0xB7, "AtheOS"},                             // 0xB7
    {0xB8, "Boot Wizard hidden"},                 // 0xB8
    {0xBB, "Boot Wizard"},                        // 0xBB
    {0xBC, "BSDI fs"},                            // 0xBC
    {0xBD, "BSDI swap"},                          // 0xBD
    {0xBE, "EFS"},                                // 0xBE
    {0xBF, "Solaris Boot"},                       // 0xBF
    {0xFB, "VMware VMFS"},                        // 0xFB
    {0xFC, "VMware VMKCORE"},                     // 0xFC
    {0xFD, "Linux raid auto"},                    // 0xFD
    {0xEE, "GPT protective MBR"},                 // 0xEE
    {0xEF, "EFI System Partition"},               // 0xEF
    {0xFF, "Xen hypervisor"}                      // 0xFF
};

const char* getPartitionType(int code) {
    int numPartitions = sizeof(types) / sizeof(types[0]);
    for (int i = 0; i < numPartitions; i++) {
        if (types[i].number == code) {
            return types[i].type;
        }
    }
    return "Unknown";
}

