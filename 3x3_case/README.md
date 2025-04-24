# A winning strategy for Determinant Tic-Tac-Toe on an nxn board

## Introduction
The rules of Determinant Tic-Tac-Toe are simple. There are two players, call them $P_0$ and $P_1$. $P_0$ and $P_1$ take turns placing 0s and 1s respectively into an nxn matrix. The goal of $P_0$ is to make the resulting matrix's determinant zero, and $P_1$'s goal is to make it non zero. Presented in our Linear Algebra tutorial with $n=3$, most quickly convinced themselves that $P_0$ always has a winning strategy. I'm concerned more so with the case of $n \geq 4$ and also whether $P_0$ going first or second matters.

## Claim
My claim is that $P_0$ can always win for $n >= 4$ regardless of who goes first. The proof is relatively intuitive and consists of breaking down the problem into that of proving the forced linear dependence of the rows of B which of course implies that the determinant of B will be 0.

## Definitions and Terminology
Let's define our board as an nxn matrix of 0s and 1s.
```math
    B \in M_n(\Set{0, 1})
```


We also want to view our board as a column of it's rows.
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


## Vector Filling Game
Let's define a new game (that might seem a little contrived at first) that we will use in the proof of our winning strategy for Determinant Tic-Tac-Toe.

Consider two vectors of length k, $P$ and $Q$. This game is very similar in vain to our Tic-Tac-Toe. Each player takes turns placing a 1 or 0 respectively into any position j on either vector. $P_0$'s goal is to fill $P$ and $Q$ such that $P + Q = (1, \dots, 1)$. That is, to make sure that $P + Q$ is equal to the vector of length k filled with ones (called the "k-ones vector" from here onwards). $P$'s goal is the opposite, that is, make $P + Q$ equal to anything *but* the k-ones vector.


Notice that if $P_0$ wins, $p_i + q_i = 1 \forall i \in \natnums s.t. 1 \geq i \geq k$.


Let's try construct a proof using mathematical induction.

#
