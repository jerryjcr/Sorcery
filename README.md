# Sorcery
## Phase 1 ✅
The first phase of the project requires us to build the core skeleton of our game, which is identified in our setup and UML.

The tasks of this phase include the following:


- Define abstract base classes/interfaces:
  - Card
  - Spell
    - useSpell is a wrapper for useAbility
  - Minion
  - Ritual
    - Handle charges
  - Ability
    - TriggerType enum
  - Subject/Observer
- Establish Player class and define basic fields
  - Ownership of subdecks: deck, hand, graveyard, etc.
- Define basic GraphicalDisplay class that observes the Players
- Build a basic game loop to test functionality of two Players with empty boards (no concrete classes exist as of yet).

## Phase 2 ✅
In the second phase of the project, we focus on extending the game loop and adding more player actions. This includes:

- Implement the actual game loop:
  - Start and end turn behaviour
- Basic player commands
  - draw
  - discard
  - play
  - use
  - attack
  - describe
  - etc.
- Parse command input
