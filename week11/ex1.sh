#!/bin/bash

# Create a 50MB image file for the LOFS
sudo fallocate -l 50M ./lofs.img

# Associate the image file with a loop device
sudo losetup -f ./lofs.img

# Format the loop device with ext4 filesystem
sudo mkfs.ext4 /dev/loop0

# Create a directory to mount the loop device
mkdir lofsdisk

# Mount the loop device to the created directory
sudo mount /dev/loop0 lofsdisk/

# Add two files to the LOFS
echo "First Name" > lofsdisk/file1
echo "Last Name" > lofsdisk/file2

# Define a function to get shared libraries of a binary file
get_libs() {
    ldd $1 | grep -o '/[^ ]*'
}

# Get shared libraries of bash, cat, echo and ls commands and add them to the LOFS
for cmd in bash cat echo ls; do
    libs=$(get_libs $(which $cmd))
    sudo cp --parents $(which $cmd) lofsdisk/
    for lib in $libs; do
        sudo cp --parents $lib lofsdisk/
    done
done



# Run the program ex1 and save the output in a file ex1.txt
gcc ex1.c -o ex1
sudo cp ./ex1 ./lofsdisk/
sudo chroot ./lofsdisk/ /bin/bash -c "/ex1" >> ex1.txt 2>&1


# Run the program ex1 again without changing the root directory and append the output to the file ex1.txt
sudo ./ex1 >> ex1.txt 2>&1

