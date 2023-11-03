# Ising Model Simulation using SDL2
This repository contains a C implementation of the Ising model simulation, a mathematical model in statistical mechanics describing ferromagnetism. The simulation utilizes the Metropolis algorithm to update the spins of a 2D lattice. The visualization is done using the SDL2 library, allowing for real-time rendering of the Ising model evolution.

## Prerequisites
* SDL2 library
* C compiler

## How to Use

1. Clone the repository: git clone https://github.com/username/repo.git
2. Compile the code using a C compiler: gcc main.c -o ising -lSDL2 -lm
3. Run the executable: ./ising

## Parameters

* ***T (Temperature)***: The temperature of the system, which affects the behavior of spins. Input the desired temperature during program execution.
* ***J (Interaction Strength)***: The interaction strength between neighboring spins. Input the desired value during program execution.
* ***Distribution of Spins***: Set the initial distribution of spins (0 - 1). Spins are randomly initialized based on this distribution

## How it Works

* The Ising model consists of discrete variables representing magnetic dipole moments of atomic spins, which can be in one of two states: up (+1) or down (-1).
* Spins are updated using the Metropolis algorithm, which calculates the change in energy for a spin flip and decides whether to accept or reject the flip based on the energy change and temperature.
* The simulation runs indefinitely, continuously updating spins and visualizing the evolving state of the system.

## Note

* The code contains a basic implementation of the Ising model and may not cover all edge cases or optimizations.
* Feel free to modify and experiment with the code to explore different aspects of the Ising model simulation.


## References
* https://en.wikipedia.org/wiki/Ising_model
* https://www.youtube.com/watch?v=vwLb3XlPCB4
* https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm
* https://www.libsdl.org/












![Screenshot_2](https://github.com/BlagojeBlagojevic/Ising-model/assets/100707842/9552fc54-dfb1-4c08-a67e-cd0736453e67)


![Screenshot_1342](https://github.com/BlagojeBlagojevic/Ising-model/assets/100707842/422ce86e-59d6-4377-9a77-25b37d11dc30)






