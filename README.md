# 🐚 minishell – Our Own Bash-like Shell in C

**minishell** is a fully functioning, minimal UNIX shell implemented in C. This project introduces core concepts of process management, file descriptors, signal handling, parsing, and I/O redirection—while also being the first **group project** in the 42 curriculum.

> 🧠 _This project took around a month and was a huge learning experience in both C and collaboration with teammates using Git._

---

## 📚 Project Overview

Create a shell that behaves similarly to `bash`, with support for:
- Built-in commands
- Pipes and redirections
- Quoting rules
- Signal handling
- Environment variable expansion

---

## 🚀 Features

### ✅ Core Functionalities

- Prompt display and input via `readline()`
- Working history (with `add_history`)
- Executing external programs from `$PATH`
- Argument parsing with:
  - `'single'` and `"double quotes"`
  - `$ENV` variable expansion
  - `$?` for last exit status

### 🔁 Redirections

| Symbol | Behavior                     |
|--------|------------------------------|
| `<`    | Redirect input               |
| `>`    | Redirect output (overwrite) |
| `>>`   | Append output                |
| `<<`   | Here-document (with limiter)|

### 🔗 Pipes

```bash
cat file.txt | grep "42" | wc -l
```

Handles n-level pipes using `pipe()` and `dup2()`.

### 🧠 Built-ins Implemented

- `echo` (with `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### 🧩 Signal Handling (Interactive Mode)

| Key Combo | Behavior                        |
|-----------|---------------------------------|
| `Ctrl+C`  | Interrupts and shows new prompt |
| `Ctrl+D`  | Exits the shell                 |
| `Ctrl+\`  | Ignored                         |

---

## 🔧 Build and Run

### 🛠️ Compilation

```bash
make
```

### ▶️ Running the Shell

```bash
./minishell
```

You’ll see a prompt where you can start typing commands.

---

## 🤝 Collaboration Reflection

This was my **first group project** at 42. It taught me:
- How to effectively collaborate using Git branches, commits, and merge strategies
- How to structure and divide work across modules
- The importance of consistent code styling and communication

---
