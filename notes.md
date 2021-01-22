## AI Notes ##

([source][1])

0-20 level system

### Levels at the beginning of each night:

| ↓Night &#124; Animatronic→ | Freddy | Bonnie | Chica | Foxy |
|----------------------------|:------:|:------:|:-----:|:----:|
| Night 1                    |    0   |    0   |   0   |   0  |
| Night 2                    |    0   |    3   |   1   |   1  |
| Night 3                    |    1   |    0   |   5   |   2  |
| Night 4                    | 1 or 2 |    2   |   4   |   6  |
| Night 5                    |    3   |    5   |   7   |   5  |
| Night 6                    |    4   |   10   |   12  |  16  |

### AI Level Increases by time:

(levels increase ***AT*** the specified time)

| ↓Time &#124; Animatronic→ | Freddy | Bonnie | Chica | Foxy |
|---------------------------|:------:|:------:|:-----:|:----:|
| 2 AM                      |        |   +1   |       |      |
| 3 AM                      |        |   +1   |   +1  |  +1  |
| 4 AM                      |        |   +1   |   +1  |  +1  |

### Power decrease interval per night:

| <ins>Night</ins>           | -1% every ___ seconds |
|----------------------------|:---------------------:|
| **Night 1**                |        9.6 (576f)     |
| **Night 2**                |          6 (360f)     |
| **Night 3**                |           5 (300f)    |
| **Night 4**                |           4 (240f)    |
| **Night 5, 6, and Custom** |           3 (180f)    |

Each of these are divided by the power level to get the current rate. (so in increments of x/3 and x/4)

### Extra Drain

According to https://freddy-fazbears-pizza.fandom.com/wiki/Power_Indicator#What_Drains_Power
there is an extra, super small drain applied each second that adds up to:

* Night 2: 1.5/hour
* Night 3: 1.8/hour
* Night 4: 2.25/hour
* Night 5+: 3/hour

## Movement

### Basic movement:

Every ___ seconds, an imaginary D20 is rolled once (separate for each animatronic). The resulting number is then
compared to each animatronic's AI level. Movement will happen if `lvl >= rnd`.

|                 |            <ins>**Freddy**</ins>            |      <ins>**Bonnie**</ins>      |            <ins>**Chica**</ins>           |                   <ins>**Foxy**</ins>                  |
|-----------------|:-------------------------------------------:|:-------------------------------:|:-----------------------------------------:|:------------------------------------------------------:|
| **Frequency:**  |                     ~~181f~~ 180f           |              298f               |                   ~~299f~~ 300f           |                          305f                           |
| **Movement:**   | [See below],<br/>**ONLY** if camera is down | Random room,<br/>left side only | Random adjacent room,<br/>right side only | Increase 1 phase,<br/>**ONLY** if unlocked (see below) |

These values have been converted to frames (assuming 60fps) and tweaked slightly to allow for an lcm the size of an int.

### Foxy

Foxy stays locked from the time the camera is opened to a random number (0.83 to 16.67) of seconds after the camera is
closed.

**RIGHT WHEN** he reaches phase 4 (starts from 0 or 1?), he will leave after either:

* The left hall is checked
* 25 seconds have passed Whichever comes first. If blocked by the door, he steals power and returns to phase 1 or 2 (50%
  chance)

#### Stolen power amount:

`-drain = 5a + 1` where `a` is the number of times Foxy has drained power that night.

### Chica and Bonnie:

Once they reach your door (separate area from any of the cameras), they will try to attack at their next successful
movement opportunity. If the door is shut, they reset to the dining area (next room from the stage)
If it's not, they "enter the room" and disable the door.

Once in the room, they will attack the next time you **lower** the camera. If you stay in/out of the camera for 30
seconds, they will attack anyway.

### Freddy

#### Dormant Phase

On a successful movement opportunity, a countdown begins. The countdown lasts `100 * (10 - lvl)` frames (at 60fps)

(yes, it hits 0 at night 10, but Freddy never goes past level 4). But on custom nights, (I assume), it has a minimum
value of 0 (it doesn't go negative or anything)

If the timer ends while the camera is up, he will "activate" as soon as the camera goes down. The timer continues even
if the camera is up, though.

After the timer ends, he enters Attack Phase.

#### Attack Phase

Upon entering Attack Phase, Freddy teleports to Cam 4B. In this phase, he is only frozen by the camera if it's on 4B. He
also cannot enter the office while the camera is **DOWN**. So: he can only attack when you're looking at a camera that
isn't his.

If blocked by a door, he returns to the hall and tries to get to the corner again to attack.

Once in the office, he will **ONLY** attack when the camera is down. Every second while your camera is down, there is a
1 in 4 chance Freddy will attack.
(does this start on lowering the camera? ie. Could you lower the camera for <1 second at a time and still be okay?)

## Power Down

All animatronics stop everything when the power goes out. Every 5 seconds, there's a 1 in 4 chance Freddy will start
playing his music. If he hasn't shown up after 20 seconds, he will do it then no matter what. After he starts playing,
the exact same routine is run to determine when the lights flicker out (1 in 4 every 5 for 20)
After that, the same routine can be run every 2 seconds to determine when he attacks.

## Misc

After a game over, there's a 1 in 10,000 chance instead of going to the title screen, you get a golden freddy jumpscare.

Every time cam 2B is checked, there is a 1 in 100,000 chance the golden freddy poster will appear (summons him)

*there is a 1 second buffer for the poster in between checks

Freddy map:

`Stage -> 4B -> ???`

## Intervals

LCM of all modified frame intervals is 130,881,600. This will fit in an int, and as such, will play nicely with the GBA.
In this way, frames can actually be counted, and this counter will not take up too much space in memory. Every
130,881,600 frames, the framecount can be polled, modulo'd, and compared to the values listed above. It should also be
possible to offset this value for situations in which animatronics are delayed.

One minute of in-game time is 90 frames. This could be lumped in with whatever needed 360 frames to only update every 4
minutes.

## Questions

* Does Foxy start at phase 1 or 0?
* Can the animatronics return to the stage?
* What does the light do to Chica and Bonnie
* Where does Freddy start when entering attack mode?
* Where can Freddy attack from?
* Where can Freddy go, and how does he get there?
* Does Freddy have a timer in Attack Mode, or does he attack as soon as he gets his movement opportunity?
* Only one animatronic can be in each room (not stage), right? Can they kick each other out? If they try to move into an
  occupied room, do they fail their movement opportunity, or try a different room?

[1]: https://youtu.be/ujg0Y5IziiY