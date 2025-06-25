
---

# 📘 Week 2 — Loop Parallelism, Scoping, and Reductions

---

## 🧭 **Lesson 6: Parallel For Loops in OpenMP**

### 🚀 Why Loops?

Loops are often the performance bottleneck in CPU-intensive applications, especially:

* Matrix operations
* Image processing
* Physics simulations

---

### 🔧 `#pragma omp parallel for`

This directive distributes loop iterations **among threads**.

#### 📄 Example: Basic Loop Parallelism

```c
#include <stdio.h>
#include <omp.h>

int main() {
    int a[10];

    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        a[i] = i * i;
        printf("Thread %d did a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
    }

    return 0;
}
```

✅ **Explanation:**

* Each iteration is **independent** → can be executed in parallel
* `omp parallel for` splits loop iterations across available threads

---

## 🧭 **Lesson 7: Variable Scoping in OpenMP**

### 🔑 Why Scope Matters

OpenMP shares all variables by default. But **some variables need to be private to each thread** to avoid conflicts.

### 🔹 Variable Types:

| Clause         | Meaning                                                     |
| -------------- | ----------------------------------------------------------- |
| `shared`       | Visible to all threads                                      |
| `private`      | Each thread gets its own copy (uninitialized)               |
| `firstprivate` | Like private, but initialized with original value           |
| `lastprivate`  | Updates value from last iteration back to original variable |

#### 📄 Example:

```c
int x = 10;

#pragma omp parallel private(x)
{
    x = omp_get_thread_num();
    printf("Thread %d has x = %d\n", omp_get_thread_num(), x);
}
```

---

## 🧭 **Lesson 8: Reductions – Avoiding Race Conditions**

> A **race condition** occurs when multiple threads update a shared variable simultaneously.

### ❌ Bad Example:

```c
int sum = 0;
#pragma omp parallel for
for (int i = 0; i < 100; i++) {
    sum += i;  // ❗ Race condition!
}
```

### ✅ Good Example – Use `reduction`:

```c
int sum = 0;
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < 100; i++) {
    sum += i;
}
```

🔍 This creates a **private copy of `sum`** for each thread and combines them at the end.

---

## 🛠 Real-World Project: Parallel Prime Counter

```c
#include <stdio.h>
#include <omp.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int count = 0;
    int N = 100000;

    #pragma omp parallel for reduction(+:count)
    for (int i = 1; i <= N; i++) {
        if (is_prime(i))
            count++;
    }

    printf("Number of primes between 1 and %d: %d\n", N, count);
    return 0;
}
```

---

## 🧪 Assignment 2

**Try these:**

1. Write a program to compute the sum of squares `1² + 2² + ... + n²` using parallel for + reduction.
2. Modify the above program to also print which thread did which iteration (use `omp_get_thread_num()`).
3. Try adding `schedule(static, 1)` vs `schedule(dynamic, 4)` and observe load balancing.

---
