
# Vector3 AimUtils for Aimbots and ESPs

This repository provides a simple and efficient implementation of a `Vector3` class designed for use in aimbots and ESPs (Extra Sensory Perception) in game hacking. The class includes essential vector operations and trigonometric functions to calculate angles and distances in 3D space.

## Features

- **Vector Operations**: Addition, subtraction, multiplication, and division of vectors.
- **Normalization**: Normalize vectors to unit length.
- ** Angle Normalization**: Normalize angles to their range
- **Distance Calculation**: Compute the distance between two vectors.
- **Angle Calculation**: Calculate yaw and pitch angles between two points for aimbots.
- **World to Screen Conversion**: Functions to convert 3D coordinates to 2D screen coordinates.

## Usage

Include the `Vector3` class in your project to perform vector arithmetic and trigonometric calculations for game hacking applications.

### Example

```cpp
#include "geom.h"

Vec3 origin(0.0f, 0.0f, 0.0f);
Vec3 target(10.0f, 10.0f, 10.0f);

// Calculate angle
Vec3 angle = CalcAngle(origin, target);

// Normalize vector
Vec3 normalized = target.Normalize();

// Calculate distance
float distance = origin.Distance(target);

// Print results
std::cout << "Angle: " << angle.ToString() << std::endl;
std::cout << "Normalized: " << normalized.ToString() << std::endl;
std::cout << "Distance: " << distance << std::endl;
