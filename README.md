# SSH Finder C

The SSH System Finder is a C program designed to scan an IP range or local network and identify systems that have SSH (Secure Shell) enabled. It provides a straightforward way to discover SSH-enabled devices within a given range of IP addresses.

## Features

- IP Range Scanning: The program allows you to specify an IP range or a local network for scanning SSH-enabled systems.
- SSH Detection: It identifies systems with SSH enabled within the specified IP range.
- Port Configuration: You can customize the port to be scanned for SSH services (default is port 22).
- Concurrent Scanning: The program performs concurrent scanning to improve efficiency and reduce scanning time.
- Detailed Output: The results include detailed information about the identified systems, such as IP address, hostname (if available), and SSH version (if detected).
- Error Handling: The program handles errors gracefully and provides informative error messages.

## Prerequisites

Before using the SSH System Finder, ensure that you have the following:

- C compiler (GCC or any C compiler of your choice) installed on your system.
- Basic understanding of C programming.

## Installation

To install and run the SSH System Finder, follow these steps:

- Clone the repository or download the source code files.

- Open a terminal or command prompt and navigate to the directory where the source code files are located.

- Compile the C program using the C compiler. For example, using GCC:

```shell
make
```

Run the program with the desired options and parameters. See the next section for available flags and their usage.

## Usage

The SSH System Finder supports the following command-line flags:

- `-h, --help`: Displays the help message and usage information.
- `-r, --range`: Specifies the IP range or local network to scan. The format can be a single IP address, a range using CIDR notation (e.g., 192.168.1.0/24), or a combination of both (e.g., 192.168.1.0/24,192.168.2.0/24).
- `-p, --port`: Specifies the port number to scan for SSH services (default is port 22).
- `-t, --threads`: Specifies the number of concurrent threads to use for scanning (default is 10) -> comming soon :).
  

The program will output a list of discovered SSH-enabled systems with their corresponding details.

## Examples

Show help message:
```shell
$ ./ssh_system_finder --help
Usage information:
        -h     --help          Display the help message and usage information
        -r     --range         The ip range to scan (ex. 192.168.0.1/24,192.168.2.0/24)
        -p     --port          The port number to scan for SSH services (default is 22)
        -t     --threads       The number of concurrent therads to use for scanning (default is 10) -> comming soon :)
Authors: Maximilian Edison <maximilianedison@gmail.com>
         BaseMax           <basemaxcode@gmail.com>
```

Scan a specific IP address for SSH services:

```shell
./ssh_system_finder -r 192.168.1.100
```

Scan multiple IP ranges for SSH services:

```shell
./ssh_system_finder -r 192.168.1.0/24,192.168.2.0/24
```

Scan a specific IP range with a custom port:

```shell
./ssh_system_finder -r 192.168.1.0/24 -p 2222
```

Scan combination of single IP and IP ranges with custom port:
```shell
./ssh_system_finder --range 94.101.184.0/22,5.34.200.25,188.121.112.0/22 --port 2222
```

## Contributing

Contributions are welcome! If you encounter any issues or have suggestions for improvements, please open an issue or submit a pull request to the GitHub repository.

## License

This project is licensed under the GPL-3.0 License.

## Acknowledgements

The SSH System Finder was inspired by the need to identify SSH-enabled systems within a network range efficiently.

Authors:

- Maximilian Edison
- Max Base

Copyright 2023, Max Base
