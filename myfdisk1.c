#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include "PartitionsTypes.h"
#define SECTOR_SIZE 512
#define MBR_SIGNATURE 0xAA55

typedef struct {
    uint8_t status;         // Boot indicator (0x80 = bootable, 0x00 = not bootable)
    uint8_t first_chs[3];   // CHS address of the first sector
    uint8_t partition_type; // Partition type (e.g., 0x05 for extended, 0x83 for Linux)
    uint8_t last_chs[3];    // CHS address of the last sector
    uint32_t lba;           // LBA of the first sector
    uint32_t sector_count;  // Number of sectors in the partition
} PartitionEntry;

uint8_t extendedPartitionNum = 0;
uint32_t extPrt_start_lba = 0;
void printPartition(const char *deviceName, int partitionNumber, const PartitionEntry *entry, uint32_t baseLBA) {
	printf("%s%-5d %-c %-8u %-8u %-8u %2uG %-3X %s\n",
           deviceName,
           partitionNumber,
           entry->status == 0x80 ? '*' : ' ',
           entry->lba + baseLBA,
           entry->lba + entry->sector_count + baseLBA - 1,
           entry->sector_count,
	   (uint32_t) ((((uint64_t) entry->sector_count * 512) + (1024 * 1024 * 1024 - 1)) / (1024 * 1024 * 1024)),
  	   entry->partition_type,
	   getPartitionType(entry->partition_type));

}

void printPartitionTableMBR(int fd, const char *deviceName) {
	char buf[SECTOR_SIZE];

    // Read the sector
    if (read(fd, buf, SECTOR_SIZE) != SECTOR_SIZE) {
        perror("Failed to read sector");
        return;
    }

    PartitionEntry *table_entry_ptr = (PartitionEntry *)&buf[446];

    uint16_t signature = *(uint16_t *)&buf[510]; // MBR signature

    // Check if the MBR signature is correct
    if (signature != MBR_SIGNATURE) {
    	    fprintf(stderr, "Invalid MBR signature: 0x%X\n", signature);
    	    return;
    }

        for (int i = 0; i < 4; i++) {
	    	if (table_entry_ptr[i].partition_type != 0x00) { // Check for valid partition type
	
		printPartition(deviceName, i + 1, &table_entry_ptr[i], 0);
		if (table_entry_ptr[i].partition_type == 0x05 || table_entry_ptr[i].partition_type == 0x0F)
		{
			extendedPartitionNum = i + 1;
			extPrt_start_lba = table_entry_ptr[i].lba;
		}
	}
    }

}

void proccessEBR(int fd, const char *deviceName)
{
	char buf[SECTOR_SIZE];
	uint32_t ebr_lba, start_lba;

	ebr_lba = extPrt_start_lba,  start_lba = ebr_lba = extPrt_start_lba;
	int i = 5;

	while(ebr_lba != 0)
	{
		if (lseek(fd, ebr_lba * SECTOR_SIZE, SEEK_SET) < 0) {
			perror("lseek failed");
	    		return;
		}
	
		if (read(fd, buf, SECTOR_SIZE) != SECTOR_SIZE) {
	    		perror("Failed to read sector");
	    		return;
		}

		PartitionEntry *firstEntery = (PartitionEntry *)&buf[446];

		if(firstEntery[0].partition_type != 0)
		{
			 printPartition(deviceName, i, &firstEntery[0], ebr_lba);
		}

		ebr_lba = firstEntery[1].lba ? firstEntery[1].lba +  start_lba : 0;
		i++;
	}

}
int main(int argc, char **argv) {

	char buf[SECTOR_SIZE];
	unsigned char buffer[SECTOR_SIZE];
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <device>\n", argv[0]);
        return 1;
    }

    // Check if the file can be accessed with read permissions
    if (access(argv[1], R_OK) != 0) {
        fprintf(stderr, "No read permission or file does not exist: '%s'\n", argv[1]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open device '%s': %s\n", argv[1], strerror(errno));
        return 1;
    }
    printf("%-9s %-7s %-10s %-4s %-7s %-4s %-2s %-5s\n", "Device",
           "Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

    printPartitionTableMBR(fd, argv[1]);

    if(extendedPartitionNum)
    {
	    proccessEBR(fd, argv[1]);
    }
    close(fd);
    return 0;
}

