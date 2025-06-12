# sim_core

A modular C++ simulation framework for building and running block-based dynamic system models, such as a bouncing ball, signal processing chains, and more. The framework is designed for extensibility and clarity, using modern C++ and a simple block-linking API.

## Features

- **Block-based simulation engine**: Compose systems from reusable blocks (integrators, gains, constants, comparators, buffers, etc.).
- **Step-based simulation**: Discrete-time simulation with configurable step size and duration.
- **Easy extensibility**: Add your own blocks by inheriting from the `Block` base class.
- **Output to CSV**: Results can be saved for plotting in Python, Excel, or other tools.
- **MIT License**: Free and open to use for anyone.

## Example: Bouncing Ball Simulation

The framework includes a bouncing ball example that models gravity, velocity, position, and bounces with energy loss.

```
gravity --> [velocity integrator] --> [position integrator] --> [ground compare]
                                                    |                |
                                                    v                |
                                              [output buffer] <-----/
```

## Building the Project

1. Ensure you have CMake and a C++17 (or newer) compiler installed.
2. Open a terminal and navigate to the project directory:
   ```
   cd sim_core
   ```
3. Create a build directory and configure the project:
   ```
   mkdir build
   cd build
   cmake ..
   ```
4. Build the project:
   ```
   cmake --build .
   ```

## Running the Example

After building, run the simulation:

```
./sim_core
```

This will generate a `results.csv` file with the simulation output.

## Plotting Results

You can plot the results using Python and matplotlib:

```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")
plt.plot(df["step"], df["value"])
plt.xlabel("Step")
plt.ylabel("Position")
plt.title("Bouncing Ball Simulation")
plt.grid()
plt.show()
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

Inspired by block-diagram simulation tools and designed for educational and research use. Contributions and suggestions are welcome!