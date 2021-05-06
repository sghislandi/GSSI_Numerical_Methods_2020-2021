# Numerical Methods at GSSI 2020/2021 Exam

Repository for HE-8 Ph.D. course at GSSI (XXXVI cycle). It includes exercises given during the lectures. The repository is mainly written in C++ with some Python inset to produce plots of the results. 

## Table of Contents 
* [Description](#gdescription)
* [Installation](#installation)

## Description
This repository contains:

* Implementation of the Simpson integration method for the function <img src="https://latex.codecogs.com/svg.image?f(x)&space;=&space;x^{4}&space;-2x&space;&plus;1" title="f(x) = x^{4} -2x +1" />;

* Implementation of Runge-Kutta ODE integration (without and with adaptive step size method) for the pendulum;

* Implementation of Crank-Nicolson PDE integration for steady-state solution of diffusion equation;

The folder 'pyplots' contains Python scripts useful to plot the results of every single executable.

## Installation
To build this project clone the repository. Inside it:

```
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
```
