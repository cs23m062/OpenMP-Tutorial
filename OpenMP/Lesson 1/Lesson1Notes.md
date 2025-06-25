---

# 🔰 **WEEK 1 — Introduction to Parallelism & OpenMP Basics**

---

## 🧭 Lesson 1: Introduction to Parallelism

### 🎓 What is Parallelism?

> **Parallel computing** is when multiple processors (or threads) execute different parts of a task simultaneously to reduce execution time.

### 🔸 Why Parallelism?

* Faster execution (e.g., video encoding, matrix operations)
* Resource utilization (multi-core CPUs)
* Solving large-scale problems (scientific simulations, ML)

### 🔸 Types of Parallelism

| Type             | Description                           | Example                                                  |
| ---------------- | ------------------------------------- | -------------------------------------------------------- |
| Data Parallelism | Same operation on chunks of data      | Adding two arrays                                        |
| Task Parallelism | Different operations run concurrently | One thread compresses images, another sends over network |

---

## 🧭 Lesson 2: Shared vs Distributed Memory

| Feature      | Shared Memory                        | Distributed Memory              |
| ------------ | ------------------------------------ | ------------------------------- |
| Memory Model | All threads share same address space | Each process has its own memory |
| Programming  | OpenMP, pthreads                     | MPI                             |
| Scalability  | Limited to system                    | Very scalable                   |
| Speed        | Faster (memory access is cheaper)    | Slower (communication overhead) |

> We’ll focus on **OpenMP**, which is a shared memory model.

---

## 🧭 Lesson 3: What is OpenMP?

> **OpenMP (Open Multi-Processing)** is an API for parallel programming in C, C++, and Fortran on shared-memory architectures.

### 🔧 Key Features

* Easy-to-use via `#pragma` directives
* Portable and scalable
* Supports loops, tasks, sections, synchronization

### 🛠 Example:

```c
#pragma omp parallel
{
   printf("Hello from thread %d\n", omp_get_thread_num());
}
```

---

## 🧭 Lesson 4: Installing & Setting Up OpenMP

### 💻 GCC Users (Linux/macOS/WSL/MinGW)

Install GCC:

```bash
sudo apt install build-essential
```

Compile with OpenMP:

```bash
gcc -fopenmp hello.c -o hello
```

Set number of threads:

```bash
export OMP_NUM_THREADS=4
```

### 💡 Windows MinGW:

Install via MSYS2 or use WSL if issues occur with Temp files.

---

## 🧭 Lesson 5: First OpenMP Program

### 📄 `hello.c`

```c
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello from thread %d\n", tid);
    }
    return 0;
}
```

Compile:

```bash
gcc -fopenmp hello.c -o hello
./hello
```

---

## 🎯 Mini Assignment 1

1. Run the program with different thread counts: `OMP_NUM_THREADS=2`, `4`, `8`.
2. Modify the program to print:

   * Total number of threads (`omp_get_num_threads()`)
   * “Master thread reporting!” for `thread 0`

---

## ❓ Quiz 1

1. What does OpenMP stand for?
2. Which model does OpenMP follow: shared or distributed?
3. Which directive is used to parallelize a region of code?
4. How do you set the number of threads for OpenMP?
5. True or False: OpenMP requires explicit thread creation.

👉 *Answers will be reviewed with explanations in the next session.*

---

## 🛠 Project Starter: Prime Checker (Sequential)

We'll build a parallel version next week.

```c
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
```

