This works with Super Mario Galaxy 2 (SB4E01). This has not been tested on other regions.

### Setup
There is particles and effects included with the module. These can be added to your `Effect.arc` with the use of [Pygapa](https://github.com/AwesomeTMC/pygapa)

### Configuration
The configuration is the same as SMG1

Obj_arg0: Beam Length: The length of the electric beam. Default is 2000.  
Obj_arg1: Water Effect Distance: If greater than 0, this controls the distance of the BeamSurface effect from the start(?) of the beam.  
Obj_arg2: Start State: -1 = Starts idling, 0 = Starts patrolling

Path ID: A valid one is required for this to work properly; Without one, the game will crash if the EyeBeamer is in patrol mode.

SW_A: When activated, the Eye Beamer will go from its waiting state to its patrolling state.

Cutscene ID / Cast ID: Whether this object can take part in a cutscene. In order for the Eye Beamer to work properly, the cutscene part where it turns over must be named "アイビーマー回転" while the part where it starts its patrol must be named "アイビーマー降下"
