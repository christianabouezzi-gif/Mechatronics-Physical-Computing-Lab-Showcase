# Truss Bridge Analysis (EK301 Project)

## Overview
This project analyzes a statically determinate truss bridge as part of EK301. The goal is to determine internal member forces, identify failure conditions, and evaluate overall structural efficiency under applied loads.

The system uses MATLAB to solve the truss using equilibrium equations and matrix methods.

---

## Key Concepts
- Static equilibrium (∑Fx = 0, ∑Fy = 0, ∑M = 0)
- Method of joints / matrix formulation
- Tension vs compression member identification
- Load distribution across truss structure

---

## Inputs
- Joint coordinates (geometry of truss)
- Member connectivity matrix
- Applied external loads
- Support reactions (pin and roller constraints)

---

## Methodology

### 1. Truss Representation
- The structure is modeled as a set of nodes (joints) and members (bars)
- Each member is assumed to carry axial force only

---

### 2. System of Equations
- Forces are solved using a linear system derived from equilibrium at each joint
- Matrix form: Ax = b

where:
- `A` = equilibrium coefficient matrix  
- `x` = unknown member forces  
- `b` = external forces vector  

---

### 3. Solving Process
- Construct global stiffness/equilibrium matrix
- Apply boundary conditions
- Solve for unknown member forces using MATLAB linear solvers

---

### 4. Force Classification
- Positive force → Tension  
- Negative force → Compression  

---

## Failure Analysis
- Each member is compared against its critical buckling or tensile strength
- Failure occurs when:
- Compression exceeds buckling limit  
- Tension exceeds material yield strength  

---

## Performance Metrics
- Maximum load capacity before failure
- Most critical member (first to fail)
- Efficiency ratio (load supported vs material used)

---

## Outputs
- Member force diagram
- Tension/compression visualization
- Failure prediction
- Critical load estimation

---

## Assumptions
- Joints are frictionless pins  
- Members are weightless  
- Loads applied only at joints  
- Linear elastic behavior  

