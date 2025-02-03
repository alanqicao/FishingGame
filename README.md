Overview
FishGame is an educational fishing game developed using C++ with the QT framework and Box2D for physics simulation. The game is designed to teach players about different types of fish and the lures used to catch them. Players can control a boat, cast lures, catch fish, and learn interesting facts about each fish they encounter. The game also includes features like a scrapbook to track caught fish, save/load functionality, and educational resources about fishing.

Features
1. Boat Control and Lure Casting
Use the A and D keys to move the boat left and right.

Click and drag the mouse to aim and throw the lure.

The lure's trajectory is simulated using Box2D, with realistic gravity and water physics.

2. Box2D Physics
The lure is a dynamic object influenced by gravity and water resistance.

Different lures have unique densities and weights, affecting how they sink and behave in the water.

Players can reset the lure at any time to try again.

3. Educational Fish Information
When a fish bites the lure, a pop-up window displays:

The fish's name.

A description of the fish.

Quick facts about the fish.

Players can "stash" the fish to add it to their scrapbook.

4. Scrapbook
Players can view all the fish they've caught in the scrapbook.

The scrapbook allows players to revisit fish facts and track their progress.

5. Save and Load Functionality
Players can save their game progress, including caught fish and scrapbook data.

Saved games can be loaded to continue progress.

Players can also start a new game, which resets all data and populates new fish.

6. Help Button
The help button provides information about the best lures to use for each fish, enhancing the educational aspect of the game.

Technologies Used
C++: The core programming language used for development.

QT Framework: Used for creating the graphical user interface (GUI) and handling user interactions.

Box2D: A physics engine used to simulate the lure's trajectory, gravity, and water interactions.

How to Play
Move the Boat: Use the A and D keys to move the boat left and right.

Cast the Lure: Click and drag the mouse to aim and throw the lure.

Catch Fish: Wait for a fish to bite the lure. Once caught, read the fish's information and decide to stash it or reset the lure.

Explore the Scrapbook: View all the fish you've caught and revisit their facts.

Save Your Progress: Use the save feature to keep track of your progress and load it later.

Learn About Fishing: Use the help button to discover the best lures for each fish.

Installation
To run FishGame, ensure you have the following dependencies installed:

QT Framework

Box2D

Steps:
Clone the repository:

bash
Copy
git clone https://github.com/yourusername/FishGame.git
Navigate to the project directory:

bash
Copy
cd FishGame
Build the project using QT Creator or your preferred C++ build tool.

Run the executable to start the game.

Contributing
Contributions are welcome! If you'd like to contribute to FishGame, please follow these steps:

Fork the repository.

Create a new branch for your feature or bug fix.

Submit a pull request with a detailed description of your changes.

License
FishGame is licensed under the MIT License. See the LICENSE file for more details.

Acknowledgments
QT Framework for providing a robust platform for GUI development.

Box2D for enabling realistic physics simulations.

The development team for their hard work and dedication to creating an educational and fun fishing game.
