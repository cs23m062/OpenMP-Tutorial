
---

### ✅ **Quiz 2 Review**

---

**1. What is the purpose of `private` clause?**
**Your Answer:**

> Used to give private variables to threads, which they can use as per their convenience.

✅ **Correct (Well phrased!)**
Each thread gets its own **uninitialized** copy of the variable. It's not shared between threads.

---

**2. What problem does the `reduction` clause solve?**
**Your Answer:**

> It solves the problem of critical section, i.e., more than one thread accessing a common memory location.

✅ **Correct.**
Without `reduction`, simultaneous writes to a shared variable can lead to **race conditions**. `reduction` creates private copies and safely merges them at the end.

---

**3. In a loop with `#pragma omp parallel for`, what happens if two threads write to the same variable?**
**Your Answer:**

> They write to the same location only.

✅ **Correct.**
And this leads to **undefined behavior or data corruption**, unless managed with synchronization or `reduction`.

---

**4. What's the difference between `private` and `firstprivate`?**
**Your Answer:**

> `firstprivate` assigns the last known value of that variable instead of garbage.

✅ **Correct with a minor clarification.**

* `private`: Each thread gets its own copy, **uninitialized** (garbage).
* `firstprivate`: Each thread gets a **copy initialized with the value the variable had before the parallel region**.

🔄 Your explanation is right; just a bit of wording improvement needed:
"Last known value" → actually the value **before entering** the parallel region (not the "last" among threads).

---

**5. Output of the code**

```c
int x = 5;
#pragma omp parallel private(x)
{
    x = omp_get_thread_num();
    printf("%d\n", x);
}
printf("Main x = %d\n", x);
```

**Your Answer:**

> Assuming 4 threads: `0 1 2 3 Main x = 5`

✅ **Correct.**
Each thread gets a private copy of `x`, sets it to its thread ID, and prints it.
The original `x` in main is untouched → still `5`.

