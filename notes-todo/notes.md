# AI Notes #

##### Sources

* [Tech Rules YT Video][1]
* [Fnaf 1 Decompiled: Frame by Frame (imgur, pastebin, pasebin)][2]

## Overview ##

The game was originally coded in Clickteam Fusion. Most timers and countdowns are hard-coded as minutes and seconds,
but some are coded as "ticks". There are 60 ticks per second.

For my purposes developing this port, since the GBA clock runs at 60fps, I'll be using the tick values.
In this document, unless otherwise indicated, I will include the original interval FIRST, and then potentially a
converted value if applicable. For example:

`3s/180f`: The original game specified an interval of 3 seconds. For my purposes, that is 180 frames.

## Animatronics

Each of the main 4 animatronics have a level, from 0-20 (same as custom night)

### Levels at the beginning of each night:

| ↓Night &#124; Animatronic→ |        Freddy         | Bonnie | Chica | Foxy |
|----------------------------|:---------------------:|:------:|:-----:|:----:|
| Night 1                    |           0           |   0    |   0   |  0   |
| Night 2                    |           0           |   3    |   1   |  1   |
| Night 3                    |           1           |   0    |   5   |  2   |
| Night 4                    | 1 or 2 (50/50 chance) |   2    |   4   |  6   |
| Night 5                    |           3           |   5    |   7   |  5   |
| Night 6                    |           4           |   10   |  12   |  16  |

### AI Level Increases by time:

At the respective time each night, the animatronics levels increase according to this chart:

| ↓Time &#124; Animatronic→ | Freddy | Bonnie | Chica | Foxy |
|---------------------------|:------:|:------:|:-----:|:----:|
| 2 AM                      |        |   +1   |       |      |
| 3 AM                      |        |   +1   |  +1   |  +1  |
| 4 AM                      |        |   +1   |  +1   |  +1  |

As indicated, Freddy's level does not increase.

### Movement

For each animatronic, every ___ seconds (different interval for each animatronic), an imaginary D20 is rolled.
The resulting number is then compared to each animatronic's AI level. Movement will happen if `lvl >= rnd`.

> NOTE: There seems to be a lot of misinformation floating around about this, with people quoting the number of seconds
> as the number of ticks, for example. I got these values straight from a decompilation [here][1].

|               | <ins>**Freddy**</ins> | <ins>**Bonnie**</ins> | <ins>**Chica**</ins> | <ins>**Foxy**</ins> |
|---------------|:---------------------:|:---------------------:|:--------------------:|:-------------------:|
| **Frequency** |     3.02s/181.2f      |     4.97s/298.2f      |     4.98s/298.8f     |    5.01s/300.6f     |

These values have been converted to frames (assuming 60fps) and tweaked slightly to allow for an lcm the size of an int.

> NOTE: Multiple animatronics CAN be in the same room at the same time. From what I can find, as well as from testing,
> Freddy can never be seen if other animatronics are in the same room as him. However, I'm not definitively sure which
> of
> Bonnie or Chica overrides the display.

#### Chica and Bonnie

Chica and Bonnie are the simplest. They start at the **Stage**, and on each successful movement, they progress through
the flowcharts seen below. If there are multiple choices, there's a 50/50 chance for each.

For both of them, when they move, if the camera is displaying the camera *they were previously in* or the one *they're
moving to*, the cameras will be stunned and replaced with static. During this time, static is shown instead. This lasts
for 5 seconds. HOWEVER: this does not affect any in-game processes that depend on the camera being up or a specific
camera being viewed. This means that if the camera is stunned and Bonnie/Chica enter/leave the camera you have open, the
static timer will reset (even though you can't technically see them). However, when the timer is reset, the camera
flicker transition does not happen as it normally would when the camera is stunned. (QUESTION: how does the static
affect the kitchen?)

Once they reach your **door** (separate area from any of the cameras), they will try to enter the **office** on their
next successful movement opportunity:

* If the door is shut, they reset to the **Dining Area**.
* If the door is open, they "enter the room" and disable the door.

Once in the room, they start a timer for 30 seconds. Once that timer runs out:

* If the camera is up, they will force it down and jumpscare you
* If the camera is not up, they will jumpscare you

Additionally, if you **lower** the camera at any point before this timer has run out, they will jumpscare you.

##### Bonnie movement scheme

| Starting Room |      Destinations       |
|:-------------:|:-----------------------:|
|     Stage     |  Backstage<br/>Dining   |
|    Dining     | Backstage<br/>West Hall |
|   Backstage   |  Dining<br/>West Hall   |
|   West Hall   | Closet<br/>West Corner  |
|    Closet     | Left Door<br/>West Hall |
|  West Corner  |  Closet<br/>Left Door   |

##### Chica movement scheme

| Starting Room |       Destinations       |
|:-------------:|:------------------------:|
|     Stage     |          Dining          |
|    Dining     |  Restrooms<br/>Kitchen   |
|   Restrooms   |  Kitchen<br/>East Hall   |
|    Kitchen    | Restrooms<br/>East Hall  |
|   East Hall   |  Dining<br/>East Corner  |
|  East Corner  | East Hall<br/>Right Door |

#### Foxy

Foxy has "phases", and a "block counter", both starting at 0 on each night.

| Number |    Description    |
|:------:|:-----------------:|
|   0    |  Curtain closed   |
|   1    |    Peeking out    |
|   2    |   Standing out    |
|   3    |       Gone        |
|   4    | Running down hall |
|   5    |      Attack       |

> NOTE: technically, these timers all start at 0 and count up once each frame, ending when `timer > target`. Then, the
> phase is updated, and the effect begins the next frame. Technically, this means that in effect there is a period of
`target + 3` frames between starting the timer and the effect being applied. If counting down from `target` until
`timer=0`, this gives a real interval of `target` frames, which is technically different, but I think was Scott's
> intention. Although the difference is 0.05 seconds, so I don't really think it makes a difference.

##### Phases 0, 1, and 2 #####

Foxy has a stun timer that is decremented every frame (60 times per second). Every 0.1s/6f the camera is up, this value
is set to a random number from 50-1050. When Foxy gets a movement opportunity, if `timer < 1`, Foxy will advance 1
phase.

##### Phase 3 #####

Once foxy reaches phase 3, the stun timer is disregarded, and another timer is started at 1500, which is decremented
every tick.

* If the timer reaches 0, he enters phase 5 (skipping phase 4)
* If the *West Hall* cam is checked, he enters phase 4

##### Phase 4 #####

Once Foxy reaches phase 4, another timer is started at 100, decremented each tick. The **West Hall** camera begins the
animation of foxy running down the hall. When the timer reaches 0, he enters phase 5

##### Phase 5 #####

When phase 5 starts:

* If the left door is closed, he will bang on the door and drain a certain amount of power (see below), then return to
  phase
  1 or 2 (NEED CLARIFICATION)
* If the left door is open, Foxy will jumpscare the player, forcing down the camera if it is up.

##### Stolen power amount: #####

`-drain = 5a + 1` where `a` is the number of times Foxy has drained power that night.

#### Freddy

This section does not cover the Power Down phase. For that information, please see the [Power Down section](#Power-Down).

Most of this information comes from [here][3].

Freddy has a timer, and a sort of "phase counter"

| Number | Description |
|:------:|:-----------:|
|   0    | Won't move  |
|   1    | Might move  |
|   2    |  Will move  |

##### Phase 0

When it's Freddy's turn to move, if the cameras are not up, he enters Phase 1.

##### Phase 1

When entering phase 1, he starts a timer that increments every tick. Once that timer reaches `1000 - (lvl * 100)` he
enters phase 2. (from level 10 onwards, this value is always 0, so he transitions to phase 2 instantly)

The timer is reset to 0 whenever you look at the camera Freddy is on.

> NOTE: I have not found concrete evidence of him not setting a timer if the cameras are up, but in-game, since Freddy
> plays a sound every time he moves, you can see that even at level 20, if you stare at the cameras for a while, he does
> not always move immediately when you close them. Sometimes there is a delay.

##### Phase 2

In phase 2, on the next frame your camera is down, he will move.

Freddy moves in this pattern:

**Stage ... -> Dining -> Restrooms -> Kitchen -> East Hall -> East Hall Corner**

Freddy will not leave the stage until Bonnie and Chica have left.

> NOTE: I am not sure how this interacts with his phases and timers. Does he fail his movement opportunity if they are
> on stage, or does he just fail each movement attempt and perpetually wait with his timer at 0?

##### East Hall Corner

When Freddy is in the **East Hall Corner**, he follows a slightly different set of rules. On his next successful
movement opportunity (as usual the cameras must be down to succeed), he will wait until the camera is up and you are
looking at any camera that is NOT the **East Hall Corner**. Then, he will attempt to enter the office.

* If the door is closed, he returns to **East Hall**
* If the door is open, he will enter the office

## Power

### Power decrease interval per night:

| <ins>Night</ins>           | -1% every ___ seconds |
|----------------------------|:---------------------:|
| **Night 1**                |      9.6 (576f)       |
| **Night 2**                |       6 (360f)        |
| **Night 3**                |       5 (300f)        |
| **Night 4**                |       4 (240f)        |
| **Night 5, 6, and Custom** |       3 (180f)        |

Each of these are divided by the power level to get the current rate. (so in increments of x/3 and x/4)

### Extra Drain

According to https://freddy-fazbears-pizza.fandom.com/wiki/Power_Indicator#What_Drains_Power
there is an extra, super small drain applied each second that adds up to:

* Night 2: 1.5/hour = 0.025%/s
* Night 3: 1.8/hour = 0.03%/s
* Night 4: 2.25/hour = 0.0375%/s
* Night 5+: 3/hour = 0.05%/s

## Power Down

All animatronics stop everything when the power goes out. Every 5 seconds, there's a 1 in 4 chance Freddy will start
playing his music. If he hasn't shown up after 20 seconds, he will do it then no matter what. After he starts playing,
the exact same routine is run to determine when the lights flicker out (1 in 4 every 5 for 20)
After that, the same routine can be run every 2 seconds to determine when he attacks.

## Misc

After a game over, there's a 1 in 10,000 chance instead of going to the title screen, you get a golden freddy jumpscare.

Every time cam 2B is checked, there is a 1 in 100,000 chance the golden freddy poster will appear (summons him)

*there is a 1 second buffer for the poster in between checks

## Office Controls

* Only one light can be activated at a time. Activating one deactivates the other.
* Lifting the camera deactivates both lights

## Intervals

LCM of all modified frame intervals is 130,881,600. This will fit in an int, and as such, will play nicely with the GBA.
In this way, frames can actually be counted, and this counter will not take up too much space in memory. Every
130,881,600 frames, the framecount can be polled, modulo'd, and compared to the values listed above. It should also be
possible to offset this value for situations in which animatronics are delayed.

One minute of in-game time is 90 frames. This could be lumped in with whatever needed 360 frames to only update every 4
minutes.

ALTHOUGH if one night is `6 hours = 6*60*90 = 32400 frames` then isn't the 130881600 thing pointless?

## Questions

* What does the light do to Chica and Bonnie

[1]: https://youtu.be/ujg0Y5IziiY

[2]: https://www.reddit.com/r/fivenightsatfreddys/comments/2x6rw8/fnaf_1_decompiled_frame_by_frame/

[3]: https://www.reddit.com/r/technicalFNaF/comments/17zsw8e/comment/ka73aln/