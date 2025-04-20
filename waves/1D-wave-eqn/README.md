# 1D Wave Equation using finite differences

## 1D Wave PDE
The 1D wave equation is a simple second order partial differencial equation:

/[
$\frac{\partial^2 u}{\partial t^2} = c^2 \frac{\partial^2 u}{\partial x^2}$
/]

where:
- u(x, t) is the deflection at a given point and time
- `c` is the wave speed (it's more than that ie its tension/linear density but we can simplify it into one const)



## Courant Condition
Using the finite difference method for derivatives restricts us in a few ways but most importantly:
\[
\frac{c \, \Delta t}{\Delta x} \leq 1
\]

The Courant Condition, which must be satisfied for numerical stability. If it does not hold, then the simulation shits itself (for lack of a better word).

We can take our chosen fixed step $\Delta t$ and simulation resolution $\Delta x$ and then restrict the domain of our "wave speed".

\[
  0 \gt c \leq \frac{\Delta x}{\Delta t}
\]

This makes pretty intuitive sense conveniently, i.e. if we increase our simulation resolution we can increase our wave speed. In a handwavy sense, our wave speed is limited based on how "fine our grid in space and time" is.
