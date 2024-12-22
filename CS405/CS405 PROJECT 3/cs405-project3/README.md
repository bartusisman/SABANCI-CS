# Solar System Implementation Report

I have developed a **3D Solar System** using WebGL, showcasing hierarchical transformations, realistic lighting, and the addition of Mars. Below is a detailed breakdown of the implementation:

## 1. Scene Graph Implementation (Task 1)
- I established a parent-child hierarchy where the Sun, Earth, Moon, and Mars inherit transformations from their respective parent nodes.
- This structure ensures that each celestial body's position and scale are updated accurately according to its node relationship.

## 2. Lighting System (Task 2)
- I enhanced the fragment shader to incorporate **ambient**, **diffuse**, and **specular** lighting components.
- I employed the Phong reflection model to achieve realistic highlights and shading effects.

## 3. Mars Addition (Task 3)
- I added Mars as a child of the Sun, positioned at \(-6\) units along the \(x\)-axis and scaled to \(0.35\).
- It rotates at **1.5 times** the speed of the Sun, with a Mars-specific texture applied for visual realism.

## Result
- The Sun functions as both the central celestial body and the primary light source.
- Earth orbits the Sun, with the Moon as its satellite.
- Mars orbits on the opposite side, benefiting from the same lighting effects.
- Each planet has a distinct rotation and accurately reflects light, creating a dynamic and engaging scene.