# Neon Pinball

**A physics-driven pinball game developed in Unreal Engine 5.**

This project was developed **solo** as a hands-on learning experience to explore Unreal Engine's C++ integration, physics system, and material shaders. It is a classic arcade pinball game focused on understanding how to build solid backend logic and connect it to frontend visuals.

## Objective

**Achieve the highest score possible before losing all your lives.**

Keep the ball in play using physics-driven flippers, hit targets to rack up points, and survive as long as possible.

## Technical Overview

This project served as my primary practice ground for learning Unreal Engine's architecture. To deeply understand the engine, **about 90% of the core gameplay logic is written in C++**, while Blueprints are used strictly for their intended strengths: UI layout (UMG), asset assignment, and visual wiring.

### 1. Physics & Interaction

Instead of faking the movement with simple animations, the flippers and ball interactions rely on the engine's Chaos physics system.

* **Physics Constraints:** The flippers (rackets) are physical bodies attached to the table using Hinge Constraints. They are driven by angular motors and torque, requiring a good understanding of mass and force application to make the ball behave naturally.
* **Practical Collision Setup:** I used simple primitive colliders for most basic objects. However, for custom and intricate meshes (like curved ramps), I opted for the **"Use Complex Collision as Simple"** setting. This was a practical choice to ensure pixel-perfect ball trajectories without the tedious process of manually building complex simple-hitboxes for custom geometry.

### 2. Custom Rendering & Shaders

* **Custom 3D Assets:** The structural components of the pinball table and the interactive elements are custom-made for this project.
* **World Position Offset (WPO):** To handle environmental reactions (like bumpers expanding when hit or the ball stretching with speed), I explored dynamic materials driven by **World Position Offset**. This allowed me to handle the visual deformation directly on the GPU via shaders, rather than relying on skeletal meshes or Blueprint timelines.

## Build Instructions

This project requires **Unreal Engine 5** and a C++ compiler environment.

### Prerequisites

* **Unreal Engine 5.x**
* **C++ IDE:** Visual Studio 2022 (with "Game development with C++" workload) or JetBrains Rider.

### Setup

1. Clone the repository to your local machine.
2. Right-click the `.uproject` file and select **Generate Visual Studio project files**.
3. Open the generated `.sln` file in your IDE.
4. Build the project using the **Development Editor** configuration.
5. Launch the `.uproject` file to open the Unreal Editor.

## 📄 License

This project is licensed under the **MIT License**.
