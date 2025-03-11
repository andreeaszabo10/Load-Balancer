Copyright Szabo Cristina-Andreea 2022-2023

# Load Balancer

## Description
This project implements a load balancing system using **Consistent Hashing**. The system simulates the distribution of key-value pairs across multiple servers to ensure balanced data allocation and efficient retrieval. The main components include server management, key-value storage, and dynamic server addition/removal.

## Features
- **Consistent Hashing** for efficient key distribution.
- Support for adding and removing servers dynamically.
- Basic key-value storage and retrieval.
- Error handling for invalid operations.
- Simple linked list data structure for internal data storage.

## Project Structure
- **`main.c`**: Entry point for the application. It reads commands from an input file and executes operations like storing, retrieving, adding, or removing servers.
- **`load_balancer.c` / `load_balancer.h`**: Core logic for consistent hashing and managing the hash ring and servers.
- **`server.c` / `server.h`**: Implements individual server operations like storing, retrieving, and deleting key-value pairs.
- **`utils.h`**: Utility functions and data structures like linked lists and hash functions.

### Input File Format
The input file should contain commands in the following format:

- **Store a key-value pair:**
```
store "key" "value"
```
- **Retrieve a value by key:**
```
retrieve "key"
```
- **Add a new server:**
```
add_server <server_id>
```
- **Remove a server:**
```
remove_server <server_id>
```

## Error Handling
- Invalid commands will result in an error message.
- The system ensures proper memory deallocation to prevent leaks.

