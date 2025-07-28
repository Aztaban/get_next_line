# get_next_line

## 📚 Project Overview

`get_next_line` is a 42 school project where the goal is to create a function that reads a file descriptor line by line, returning one line each time it’s called — just like reading a file with `fgets()`, but with custom memory management and buffer handling.

### 🔧 Function Prototype
```c
char *get_next_line(int fd);
```
- Returns the next line from a file descriptor
- Includes the \n if present
- Returns NULL on EOF or error
- Bonus for multiple file descriptors included

## ✅ Requirements
- No memory leaks
- One line per call
- Handle multiple file descriptors (bonus)
- Norm compliant

## 🧪 Compilation Example
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

## 📁 Files
- get_next_line.c
- get_next_line_utils.c
- get_next_line.h

## 👤 Author

Created and maintained by [Martin Justa](https://github.com/aztaban) as part of the 42 school curriculum.