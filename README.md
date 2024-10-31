# ls implementation

A basic implementation of the `ls` command that lists directory contents. This implementation supports both standard listing and showing hidden files with the `-a` option.

## Features

- Lists files and directories in the current directory
- `-a` flag to show hidden files (files starting with a dot)
- Basic formatting for readability
- Color-coded output (directories in blue, regular files in white)

## Building

To compile the program:

```bash
$ make
```

## Usage

### Basic Usage
To list files in current directory (excluding hidden files):
```bash
$ ./ls
```

### Show Hidden Files
To list all files including hidden ones (files that start with a dot):
```bash
$ ./ls -a
```

## Examples

Standard listing:

![image](https://github.com/user-attachments/assets/5d2dcd4a-008d-4431-bade-545b48771716)


Listing with hidden files:

![image](https://github.com/user-attachments/assets/38652a0c-408d-45af-b94d-4c8bf3244ed8)


## Cleaning Up

To remove compiled files and executables:
```bash
$ make clean
```

## Technical Details

- Written in C
- Uses standard POSIX directory reading functions
- Implements basic error handling
- Supports standard Unix-like hidden file conventions

## Limitations

- Does not support all options available in GNU ls
- Limited to current directory (no path arguments supported)
- Basic formatting only
- No sorting options
