# Personal CMD (Custom Command-Line Terminal in C)

![C](https://img.shields.io/badge/language-C-blue.svg)
![OS](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/status-active-success.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen)

A **custom command-line interface (CLI) written in C**, designed to mimic basic terminal commands such as `ls`, `pwd`, `mkdir`, `touch`, `read`, `write`, `delete`, and more.  
This project provides a **personal shell-like environment** where users can perform file and directory operations with error handling and built-in help.

---

## 🎯 Project Overview
The **Personal CMD** project is built to strengthen knowledge of **Operating System concepts** and **System Programming in C**.  

It demonstrates:
- **Low-level file handling** using system calls (`open`, `read`, `write`, `creat`, `unlink`).
- **Directory management** (`mkdir`, `rmdir`).
- **Command parsing** using string manipulation and `sscanf`.
- **Error handling** with predefined error codes.
- Practical exposure to how **shells/terminals work internally**.

---

## ⚙️ Features

Supported commands in the terminal:

| Command | Description |
|---------|-------------|
| `clear` | Clears the screen |
| `ls` | Lists files and folders (`dir` for Windows) |
| `pwd` | Shows the current directory (`cd` for Windows) |
| `help` | Displays all available commands |
| `man <command>` | Shows detailed manual for a specific command |
| `mkdir <folder>` | Creates a new folder |
| `touch <filename> [permissions]` | Creates a file (default `0777` permission) |
| `write <filename>` | Appends data into a file |
| `read <filename>` | Reads and displays contents of a file |
| `delete file <filename>` | Deletes a file |
| `delete folder <foldername>` | Deletes an empty folder |
| `exit` | Exits the terminal |

---

## 📂 Project Structure
personal-cmd/
│── cmd11.c # Source code
│── Makefile # For building with make
│── .gitignore # Ignored files
│── README.md # Documentation
│── LICENSE # License file

---

## 🛠️ Build & Run Instructions

### Compile
```bash
gcc cmd11.c -o personal_cmd

Run
./personal_cmd

---

📖 Learning Outcomes

Working with POSIX system calls instead of standard library functions.

File descriptors, permissions, and error handling.

Basics of command interpreters / shells.

Experience with string parsing and system commands in C.

---
