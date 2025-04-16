# Classical Cryptography Algorithms in C

This project contains implementations of various classical encryption algorithms in C. It is intended for educational purposes to understand how these algorithms work at a basic level.

## 🔐 Algorithms Implemented

- **Caesar Cipher**
- **Atbash Cipher**
- **August Cipher**
- **Affine Cipher**
- **Vigenère Cipher**
- **Gronsfeld Cipher**
- **Beaufort Cipher**
- **Autoclave / Running Key Cipher**
- **N-gram Operations**
- **Hill Cipher**
- **Rail Fence Cipher**
- **Route Cipher**
- **Myszkowski Cipher**

## 🛠️ Technologies Used

- Language: **C Programming**
- Compiler: GCC / any C compiler

## 📁 Project Structure

All algorithm implementations are provided in separate `.c` files for modularity and clarity.

> ❗ **Note:**  
> Although each algorithm has its own `.c` file, the project is designed to be run using the `main.c` file.  
> `main.c` acts as the driver program that provides access to all encryption methods.

### Example structure:
Caesar.c --> Caesar Cipher logic Vigenere.c --> Vigenère Cipher logic Hill.c --> Hill Cipher logic ... main.c --> Menu-driven program to access all ciphers


## ▶️ How to Compile and Run

Use the terminal or command prompt and compile all `.c` files together with `main.c`.

```bash
gcc main.c Caesar.c Atbash.c August.c Affine.c Vigenere.c Gronsfeld.c Beaufort.c Autoclave.c Ngram.c Hill.c RailFence.c Route.c Myszkowski.c -o crypto
./crypto





