# Linear Regression for CPU Performance

**Tiny Project**  
**Author:** Cao Đăng Trí  
**Student ID:** 10423112  
**Project Type:** Individual

---

## Project Description

This project builds a simple linear regression model to predict CPU performance (PRP - Published Relative Performance) based on hardware attributes. The entire implementation is done from scratch in C++ using self-made classes for `Vector`, `Matrix`, and `LinearSystem`.

---

## Dataset

- **Source:** [UCI Computer Hardware Data Set](https://archive.ics.uci.edu/ml/datasets/Computer+Hardware)
- **Total Samples:** 209
- **Input Features:**
  - MYCT (Machine cycle time)
  - MMIN (Minimum memory)
  - MMAX (Maximum memory)
  - CACH (Cache size)
  - CHMIN (Minimum channels)
  - CHMAX (Maximum channels)
- **Target Variable:** PRP (Published Relative Performance)

---

## Methodology

- Load and preprocess dataset from `machine.data`
- Construct feature matrix `A` and target vector `b`
- Solve the normal equation: `(AᵗA)x = Aᵗb`
- Use Gaussian elimination for solving the linear system

---

## Result

- **RMSE (Root Mean Square Error) on test set:** `99.1981`

---

## Build & Run

### Compile:
```bash
g++ -std=c++11 main.cpp Matrix.cpp Vector.cpp LinearSystem.cpp -o my_program.exe
