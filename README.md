# 🐚 mshell — minimal Unix shell

**mshell** is a custom minimal Unix shell written in C. It supports basic shell features such as pipelines, redirections, and logical operators.

This project is mainly for educational and experimental purposes, so bugs and unstable behavior are expected.

---

## ⚙️ Features

mshell supports:

- `|` — pipes  
- `>` — redirect stdout to file  
- `>>` — append stdout to file  
- `<` — redirect stdin from file  
- `&&` — logical AND  
- `||` — logical OR  
- `<<` — here-document (if implemented correctly)  
- execution of external programs

Additional features:

- execution of `~/.mshellrc` on startup  
- custom prompt  
- signal handling (`SIGINT`, `SIGTERM`)  

---

## 🚀 Build & Run

```bash
git clone https://github.com/daynizm2000/mshell.git
cd mshell
make
./mshell
