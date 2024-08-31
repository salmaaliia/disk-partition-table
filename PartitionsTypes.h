#ifndef TYPES_H_
#define TYPES_H_

// Define the partition struct
typedef struct {
    int number;         // Partition number
    const char *type;   // Partition type as a string
} Partition;
extern Partition partitions[];

const char* getPartitionType(int code);

#endif
