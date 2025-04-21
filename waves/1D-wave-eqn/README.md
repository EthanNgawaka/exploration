# 1D Wave Equation using finite differences

## 1D Wave PDE
The 1D wave equation is a simple second order partial differencial equation:

```math
  \frac{\partial^2 u}{\partial t^2} = c^2 \frac{\partial^2 u}{\partial x^2}
```

where:
- u(x, t) is the deflection at a given point and time
- c is the wave speed (it's more than that ie its tension/linear density but we can simplify it into one const)


## Numerical Differentiation
So how do we actually solve this PDE? Well it's pretty easy actually, [this](https://www.youtube.com/watch?v=dKyqCPjhv0I) is a really great video for this topic.
The main idea is to use the taylor series expansion of $u(x + \Delta x)$ and $i(x - \Delta x)$ and manipulate those to extract the $u''(x)$ term that we want. Those taylor series look like this:
```math
  u(x + \Delta x) = u(x) + \Delta x \, u'(x) + \frac{(\Delta x)^2}{2} \, u''(x) + \frac{(\Delta x)^3}{6} \, u^{(3)}(x) + \frac{(\Delta x)^4}{24} \, u^{(4)}(x) + \cdots
```
```math
  u(x - \Delta x) = u(x) - \Delta x \, u'(x) + \frac{(\Delta x)^2}{2} \, u''(x) - \frac{(\Delta x)^3}{6} \, u^{(3)}(x) + \frac{(\Delta x)^4}{24} \, u^{(4)}(x) - \cdots
```

looking at them it's pretty clear we can combine them in the following way to almost entirely extract $u''(x)$:
```math
  u''(x) \approx \frac{u(x + \Delta x) - 2u(x) + \Delta x \, u'(x)}{(\Delta x)^2} + \mathcal{O}(\Delta x)
```
notice that trailing term, it's written here with big O notation to indicate that the trailing end of the taylor series grows with the square of $\Delta x$. This is our error term. There are some fancy things you can do to increase precision but we aren't *really* going for accuracy so this is fine.

Ok so hand wavy hand wavy I wrote all that latex out for a single variable ODEs but it's easy enough to see it extended to our PDE we had at the start. So let's sub these bad boys into our PDE!
```math
  \frac{u_{x,\,t+\Delta t} - 2u_{x,\,t} + u_{x,\,t-\Delta t}}{(\Delta t)^2}
  =
  c^2 \frac{u_{x+\Delta x,\,t} - 2u_{x,\,t} + u_{x-\Delta x,\,t}}{(\Delta x)^2}
```

Boom, rearranging now for our $u_{x,t+\Delta t}$ (i.e. our deflection at the next timestep), we arrive at the following:
```math
  u_{x,\,t+\Delta t} =
  2u_{x,\,t} - u_{x,\,t-\Delta t} +
  \left( \frac{c \, \Delta t}{\Delta x} \right)^2
  \left( u_{x+\Delta x,\,t} - 2u_{x,\,t} + u_{x-\Delta x,\,t} \right)
```
well, well, well. Our deflection for the next timestep is dependent on the function value at *previous* timesteps! Riveting stuff.
Note that we also need the deflection at the position before and after a given $x$, thus we need to handle boundary conditions. There are a few things you can do here but for now, I'm just going to stick with fixed boundary points but there are some really cool things we can do later on maybe.
Our fixed Dirichlet boundary condition (named after big man Johann Dirichlet) looks like this:
```math
  u(0, t) = 0, \quad u(L, t) = 0 \quad \text{for all } t \geq 0
```

We also should probably set an initial condition, this can literally be anything; data points, actual analytic funcs, etc. For now let's just set it to a classic test case for the 1D wave equation, the Gaussian wave. This just looks like our good old Gaussian distribution.
```math
  u(x, 0) = A \exp\left(-\frac{(x - x_0)^2}{2 \sigma^2}\right)
```
We can do the same for velocity, let's just set it to 0.
```math
\frac{\partial u}{\partial t}(x, 0) = 0
```

## Courant Condition
Using the finite difference method for derivatives restricts us in a few ways but most importantly:

```math
  \frac{c \, \Delta t}{\Delta x} \leq 1
```

The Courant Condition, which must be satisfied for numerical stability. If it does not hold, then the simulation shits itself (for lack of a better word).

We can take our chosen fixed step $\Delta t$ and simulation resolution $\Delta x$ and then restrict the domain of our "wave speed".

```math
  0 \gt c \leq \frac{\Delta x}{\Delta t}
```

This makes pretty intuitive sense conveniently, i.e. if we increase our simulation resolution we can increase our wave speed. In a handwavy sense, our wave speed is limited based on how "fine our grid in space and time" is.

## Timestep fuckery
Unfortunately frame time and computer speed must be taken into account. This isn't too difficult, we can change our update function to do a simple accumulative fixed timestep.

## Splishy Splashy (Making it look and feel more like water)
Now that we have a pretty solid 1D wave equation solution using numerical methods, we can get to work on making it feel more like water. Tuning our constants dt, dx, and c till we get something nice yields the following:
```math
  \delta t = 0.016
```
```math
  \delta x = 5
```
```math
  c = 300
```
This produces something that feels pretty close to water. While not perfect, it would feel right at home in a simple 2D platformer or something along those lines.

There are a few things that remain off still. Namely, when applying impulses to our water it feels choppy and sluggish. This is due to the (naive) approach taken of applying forces to a single point or equally to a set of nearby points. The first solution that comes to mind (and a probably terribly inefficient one) is to derive a gaussian distribution with values such that the curve is centered at the point of interaction and spread out nicely accross the surrounding area. This is pretty simple, our $x_0$ simply becomes our "ground zero" point and the other constants can be tuned depending on the interaction strength etc. With that, our jaggedness and sharp edges are no more. Now we just have a very *sludgy* feeling liquid. To fix this, a simple restoring force can be applied to the entire field with a simple += on each point.

*Finally* we have something that looks pretty ok.

## Performance
This terribly quick and dirty implementation is not the most performant code possible by far, but still runs pretty well for what it is. I can spawn 150 instances of our WaterSim object and still get 150fps while simply simulating wave propagation. *Interacting* with the simulation is another deal entirely. Whenever a wave is interacted with, the entire set of points is iterated over, making it extremely inefficient. Interacting with all 150 waves at once can simply crash the program, even just 10 tanks the fps. Obviously this is simply because of the way I've done it here specifically. One would never use this approach in a game or something, maybe only applying the Gaussian to close neighbours or other various speed ups.

## Final thoughts
In the end this was surprisingly simple, an afternoon of wrapping my head around finite difference differentiation and another of banging it out in code. While the actual implementation leaves a lot to be desired, the foundations are there. I will probably end up coming back and doing some work with shaders and particles to try touch it up but for now the mesmerising motion of simple harmonic motion will have to do.


I'm going to go on further into the world of fluid simulation so this was just me getting my toes wet but I'm pretty confident that you'd be hard pressed to find something that runs this fast and produces effects this nice.

## Further Explorations
- Rendering: Shaders and particles to *actually* water nicely.
- Physics: Simple bouyancy and other such interactions to make pretty splish splash.
- Optomization: Further improving the efficiency (especially of interactions) and properly benchmark them.
- Modularity: Generally improve structure and flexibility of code to make it easier to plop into other projects.


## Sources
- https://www.youtube.com/watch?v=dKyqCPjhv0I
- https://en.wikipedia.org/wiki/Wave_equation
