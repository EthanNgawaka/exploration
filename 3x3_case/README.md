# A winning strategy for Determinant Tic-Tac-Toe on an nxn board

## Introduction
The rules of Determinant Tic-Tac-Toe are simple. There are two players, call them $P_0$ and $P_1$. $P_0$ and $P_1$ take turns placing 0s and 1s respectively into an nxn matrix. The goal of $P_0$ is to make the resulting matrix's determinant zero, and $P_1$'s goal is to make it non zero. Presented in our Linear Algebra tutorial with $n=3$, most quickly convinced themselves that $P_0$ always has a winning strategy. I'm concerned more so with the case of $n \geq 4$ and also whether $P_0$ going first or second matters.


My claim is that $P_0$ can always win for $n >= 4$ regardless of who goes first. The proof is relatively intuitive and consists of breaking down the problem into that of proving the forced linear dependence of the rows of B which of course implies that the determinant of B will be 0.

## Definitions and Terminology
Let's define our board as an nxn matrix of 0s and 1s.
```math
    B \in M_n(\Set{0, 1})
```


It is also useful to view our board as a column of it's rows.
```math
    B = \begin{bmatrix}
        R_1 \\
        \vdots \\
        R_n \\
    \end{bmatrix}
```
```math
    R_i = (r_1, \dots, r_n)
```

