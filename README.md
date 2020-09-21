# 20F-TM
Notebooks and codes for the course [Thermal Modeling: From Semiconductor to Medical Devices and Personalized Therapy Planning](http://www.vvz.ethz.ch/Vorlesungsverzeichnis/lerneinheit.view?lerneinheitId=138598&semkez=2020S&ansicht=KATALOGDATEN&lang=en), FS2020 @ETHZ


## Course synopsis

In this 13-week sequence, students learn how to write programs from scratch to solve partial differential equations that are useful for Earth science applications. Programming will be done in MATLAB and will use the finite-difference method and marker-in-cell technique. The course will emphasise a hands-on learning approach rather than extensive theory.

## Objective
The goal of this course is for students to learn how to program numerical applications from scratch. By the end of the course, students should be able to write state-of-the-art MATLAB codes that solve systems of partial-differential equations relevant to Earth and Planetary Science applications using finite-difference method and marker-in-cell technique. Applications include Poisson equation, buoyancy driven variable viscosity flow, heat diffusion and advection, and state-of-the-art thermomechanical code programming. The emphasis will be on commonality, i.e., using a similar approach to solve different applications, and modularity, i.e., re-use of code in different programs. The course will emphasise a hands-on learning approach rather than extensive theory, and will begin with an introduction to programming in MATLAB.


## Content
A provisional week-by-week schedule (subject to change) is as follows:

- Week 1: Introduction to the finite difference approximation to differential equations. Introduction to programming in Matlab. Solving of 1D Poisson equation.
- Week 2: Direct and iterative methods for obtaining numerical solutions. Solving of 2D Poisson equation with direct method. Solving of 2D Poisson equation with Gauss-Seidel and Jacobi iterative methods. 
- Week 3: Solving momentum and continuity equations in case of constant viscosity with stream function/vorticity formulation. 
- Weeks 4: Staggered grid for formulating momentum and continuity equations. Indexing of unknowns. Solving momentum and continuity equations in case of constant viscosity using pressure-velocity formulation with staggered grid. 
- Weeks 5: Conservative finite differences for the momentum equation. "Free slip" and "no slip" boundary conditions. Solving momentum and continuity equations in case of variable viscosity using pressure-velocity formulation with staggered grid. 
- Week 6: Advection in 1-D. Eulerian methods. Marker-in-cell method. Comparison of different advection methods and their accuracy. 
- Week 7: Advection in 2-D with Marker-in-cell method. Combining flow calculation and advection for buoyancy driven flow. 
- Week 8: "Free surface" boundary condition and "sticky air" approach. Free surface stabilization. Runge-Kutta schemes. 
- Week 9: Solving 2D heat conservation equation in case of constant thermal conductivity with explicit and implicit approaches. 
- Week 10: Solving 2D heat conservation equation in case of variable thermal conductivity with implicit approach. Temperature advection with markers. Creating thermomechanical code by combining mechanical solution for 2D buoyancy driven flow with heat diffusion and advection based on marker-in-cell approach. 
- Week 11: Subgrid diffusion of temperature. Implementing subgrid diffusion to the thermomechanical code.
- Week 12: Implementation of radioactive, adiabatic and shear heating to the thermomechanical code.
- Week 13: Implementation of temperature-, pressure- and strain rate-dependent viscosity, temperature- and pressure-dependent density and temperature-dependent thermal conductivity to the thermomechanical code.
