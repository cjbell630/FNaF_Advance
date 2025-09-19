# FNaF 1 Breakdown #

##### Sources

* [Fnaf 1 Decompiled: Frame by Frame (imgur, pastebin, pastebin)][2]
* [Easter Egg Chances Video][4]
* [Tech Rules YT Video][1] (contains a lot of inaccurate information)

Table of Contents
=================

* [Overview](#Overview)
* [Animatronics](#Animatronics)
    * [Levels at the beginning of each night](#Levels-at-the-beginning-of-each-night)
    * [AI Level Increases by time](#AI-Level-Increases-by-time)
    * [Movement](#Movement)
        * [Chica and Bonnie](#Chica-and-Bonnie)
            * [Bonnie movement scheme](#Bonnie-movement-scheme)
            * [Chica movement scheme](#Chica-movement-scheme)
        * [Foxy](#Foxy)
        * [Freddy](#Freddy)
* [Power](#Power)
    * [Power drain rate](#Power-drain-rate)
    * [Power Down](#Power-Down)
* [Misc Effects](#Misc-Effects)
    * [Title screen twitching (title Active 2)](#Title-screen-twitching-title-Active-2)
    * [Static overlay (title )](#Static-overlay)
    * [Flickering (Random number 3C)](#Flickering-Random-number-3C)
    * [Night 4+ 2b/4b effects (Random number 3F)](#Night-4-2b4b-effects-Random-number-3F)
    * [Fullscreen Hallucinations (Active 21)](#Fullscreen-Hallucinations-Active-21)
    * [Cam Hallucinations](#cam-hallucinations)
    * [Bonnie/Chica close/far](#BonnieChica-closefar)
    * [Window jumpscare sound](#Window-jumpscare-sound)
    * [Phone call mute button](#Phone-call-mute-button)
    * [Clock](#Clock)
    * [Golden Freddy](#Golden-Freddy)
    * [Game Over Golden Freddy Jumpscare](#Game-Over-Golden-Freddy-Jumpscare)
    * [Rare Bonnie Jumpscare](#Rare-Bonnie-Jumpscare)
    * [Office breath (Active 2E)](#Office-breath-Active-2E)
* [Office Controls](#Office-Controls)
* [Intervals](#Intervals)
* [Questions](#Questions)

## Overview

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

| ↓Time &#124; Animatronic→ | Bonnie | Chica | Foxy |
|---------------------------|:------:|:-----:|:----:|
| 2 AM                      |   +1   |       |      |
| 3 AM                      |   +1   |  +1   |  +1  |
| 4 AM                      |   +1   |  +1   |  +1  |

As indicated, Freddy's level does not increase.

### Movement

For each animatronic, every ___ seconds (different interval for each animatronic), an imaginary D20 is rolled.
The resulting number is then compared to each animatronic's AI level. Movement will happen if `lvl >= rnd`.

> NOTE: There seems to be a lot of misinformation floating around about this, with people quoting the number of seconds
> as the number of ticks, for example. I got these values straight from a decompilation [here][1].

|               | <ins>**Freddy**</ins> | <ins>**Bonnie**</ins> | <ins>**Chica**</ins> | <ins>**Foxy**</ins> |
|---------------|:---------------------:|:---------------------:|:--------------------:|:-------------------:|
| **Frequency** |     3.02s/181.2f      |     4.97s/298.2f      |     4.98s/298.8f     |    5.01s/300.6f     |

> NOTE: Multiple animatronics CAN be in the same room at the same time, but only one is displayed.
> The order is (front layer > back layer): Chica > Bonnie > Freddy 
> (also, Foxy's hall animation will play regardless of whether Bonnie is in the hall)
> Freddy can never be seen if other animatronics are in the same room as him. 

#### Chica and Bonnie

Chica and Bonnie are the simplest. They start at the **Stage**, and on each successful movement, they progress through
the flowcharts seen below. If there are multiple choices, there's a 50/50 chance for each.

For both of them, when they move, if the camera is displaying the camera *they were previously in* or the one *they're
moving to*, the cameras will be stunned and replaced with static. During this time, static is shown instead. This lasts
for 5s/300f. HOWEVER: this does not affect any in-game processes that depend on the camera being up or a specific
camera being viewed. This means that if the camera is stunned and Bonnie/Chica enter/leave the camera you have open, the
static timer will reset (even though you can't technically see them). However, when the timer is reset, the camera
flicker transition does not happen as it normally would when the camera is stunned. (QUESTION: how does the static
affect the kitchen?)

Once they reach your **door** (separate area from any of the cameras),
Bonnie switches off the hall light if it is on (for some reason Chica does not)
and they will try to enter the **office** on their next successful movement opportunity:

* If the door is shut, they reset to the **Dining Area**.
* If the door is open, they "enter the room" and disable the door and lights on their respective side.

They CAN enter when the lights are on, and because they disable the lights, the hall light shuts off when they enter.

Once in the room, the next frame that the cameras are up, they start a timer for 30s/1800f.
Once that timer runs out, if the camera is still up, they will force it down and jumpscare you.

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

This section does not cover the Power Down phase. For that information, please see
the [Power Down section](#Power-Down).

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

Then, he goes back to Phase 0 (?)

Freddy will not leave the stage until Bonnie and Chica have left.

> NOTE: I am not sure how this interacts with his phases and timers. Does he fail his movement opportunity if they are
> on stage, or does he just fail each movement attempt and perpetually wait with his timer at 0?

##### East Hall Corner

When Freddy is in the **East Hall Corner**, he follows a slightly different set of rules. On his next successful
movement opportunity (as usual the cameras must be down to succeed), he will begin waiting until the camera is up and
you are looking at any camera that is NOT the **East Hall Corner**. Then, he will attempt to enter the office.

* If the door is closed, he returns to **East Hall**
* If the door is open, he will enter the office

> NOTE: unlike Bonnie and Chica, Freddy does not disable the doors and lights when he enters the office.

##### Office

Every 1s/60f Freddy is in the office, if the camera is down, he has a 1 in 5 chance of jumpscaring you.

> NOTE: I'm not 100% sure about this order. Is it "is cam down -> wait 1s -> try jumpscare" or "wait 1s -> is cam
> down -> try jumpscare"?
> (the answer is prob the timer counts down every frame the cams are down, and resets every frame the cams are up)

## Power

### Power drain rate

Every second, 0.1% power is drained per bar on the usage meter.

Additionally, starting on Night 2, an additional 0.1% is drained at an interval dependent on the night number:

| <ins>Night</ins>           | -0.1% every ___ |
|----------------------------|:---------------:|
| **Night 2**                |     6s/360f     |
| **Night 3**                |     5s/300f     |
| **Night 4**                |     4s/240f     |
| **Night 5, 6, and Custom** |     3s/180f     |

### Power Down

All animatronics stop everything when the power goes out.

The camera popup icon disappears, and the doors and lights are no longer responsive.
(meaning, not only do they not work, but they also do not play the disabled sfx)
Honking and scrolling the cams still works, however.

Power down phases:

| Number | Description |
|:------:|:-----------:|
|   0    |   Waiting   |
|   1    |  Music box  |
|   2    |  Blackout   |
|   3    |  Jumpscare  |

At the start of each phase, a timer is set for 20s/1200f. When that timer hits 0, the next phase will be triggered.

#### Phase 0

Every 5s/300f, there is a 20% chance of advancing to phase 1.

#### Phase 1

A timer is set for 20s/1200f. The music box sound is played. Every 0.05s/3f there is a 25% chance of Freddy's face being
visible in the doorway and 75% chance of it being invisible.

Every 5s/300f, there is a 20% chance of advancing to phase 2.

#### Phase 2

A timer is set for 20f. While this timer is greater than 0, every frame there is a 50% chance of seeing the blackout
screen and 50% chance of seeing the powered-down office.

Once that timer hits 0, the blackout screen is shown.

Every 2s/120f, there is a 20% chance of advancing to phase 3.

#### Phase 3

Freddy jumpscares the player, and the game ends.

## Misc Effects

see line 219 in pastebin for some jumpscare timings

### Title screen twitching (title Active 2)

Every 0.08s/4.8f there is a 97% chance the normal Freddy head is shown, and a 1% chance each of the following is shown:

* Open mouth
* Twitch
* Endoskeleton exposed

TODO it also seems like the alpha is randomized? How often?

### Static overlay

TODO different rules for title

Every 1s/60f, value B is set to random # 1-3 inclusive.

Every tick, the alpha of the static overlay is set to:

`150 + (random # 0-49) + (B*15)`

### Flickering (Random number 3C)

Set to a random number 1-10 inclusive every tick

* Office light has 1/10 chance of being off, else on
* West Hall light has 7/10 chance of being off, else on

> NOTE: I'm not completely sure if the two lights are independent (ie. if it's `if/else, if/else` or
`if/elseif/elseif/else`)

### Night 4+ 2b/4b effects (Random number 3F)

Determines the twitch effects on Bonnie/Chica in West/East Corners starting on Night 4
Set to random 1-30 inclusive every 0.05s/3f
> !!! Effects only apply starting on Night 4!

* 24/30 = 12/15 chance for Normal
* 4/30 = 2/15 chance for Twitch
* 2/30 = 1/15 chance for Open Mouth

### Fullscreen Hallucinations (Active 21)

Every 1s/60f, there is a 1/1000 chance hallucinations will begin.

When hallucinations begin, they will last for 99f

Each frame hallucinations are active, there is a 1/10 chance they are visible (meaning, they flicker off and on)

> NOTE: I'm not 100% sure but I believe the hallucinations cycle between
> *Freddy, It's me (bottom right), Bonnie, It's me (upper left)* each frame no matter what,
> and is simply shown and hidden, which gives the illusion of randomizing frames

### Cam hallucinations

All cam hallucinations except for Golden Freddy are controlled by the same random value,
set to 1-100 inclusive when the cams are down. I am not sure how often this value is set.
[Source][4]

* Backstage masks looking at camera (unsure, possibly 5/100)
* East Hall Corner missing kids posters: 97,98,99,100
    * Order is likely Kids missing, shutdown sanitation, suspect convicted, years end
* East Hall crying child poster: 99
* East Hall it's me poster: 100
* West Hall Corner Freddy ripping head off: 1
* All of these are 1-10 inclusive (<=10)
    * Pirate's cove it's me
    * Stage Freddy staring at camera
    * Backstage Bonnie staring at camera

### Bonnie/Chica close/far

50% chance of each when entering room

### Window jumpscare sound

TODO

### Phone call mute button

Stays on screen for 40 seconds

### Clock

Starts at 12, incremented 1 every 90s/5400f

### Golden Freddy

Every 1s/60f, pick random number 0-34464 inclusive. If 1, golden freddy is set to appear.
> NOTE: intended behavior from Scott was 1 in 100000, but due to Clickteam 2.5 random function integer max value, the
> true odds are 1 in 34464

Whenever cam 2b is viewed, if Bonnie is not there and Golden freddy is set to appear (above value=1),
the poster will be shown, and Golden Freddy will be in the office when the cam is closed.

When the cam is closed and Golden Freddy is in the office, a timer is incremented. If that timer reaches 300,
Golden Freddy jumpscares the player. If the camera is opened while Golden Freddy is onscreen, he will disappear.
> NOTE: Does the timer get reset, or does it persist through the whole night?

### Game Over Golden Freddy Jumpscare

On the game over screen, after 10 seconds, every second there is a 1 in 10000 chance Golden Freddy will jumpscare the
player.
> NOTE: When does "10s" start? Is it at the static, at the game over text, Mike's death screen?

### Rare Bonnie Jumpscare

1/1000 chance on title after warning displayed.
TODO potential trigger on game over?

When triggered, the image is shown for 9.5s/570f, then for 0.5s/30f seconds the eyes are shown, then the player is taken
to the title screen.

### Office breath (Active 2E)

Every 5s/300f, if the player is looking at the cams and Bonnie/Chica is in office,
there is a 1/3 chance a (random?) raspy breath sound plays

### Jumpscare animations

Bonnie and Chica can only jumpscare you when the cameras are up. However, Freddy can only jumpscare when the cams are
down, and Foxy can do both. This means their jumpscare animations run directly from the office background image.

## Office Controls

* Only one light can be activated at a time. Activating one deactivates the other.
* Lifting the camera deactivates both lights.
* Buttons have a cooldown of 10f between clicks.

## Intervals

LCM of all modified frame intervals is 130,881,600. This will fit in an int, and as such, will play nicely with the GBA.
In this way, frames can actually be counted, and this counter will not take up too much space in memory. Every
130,881,600 frames, the framecount can be polled, modulo'd, and compared to the values listed above. It should also be
possible to offset this value for situations in which animatronics are delayed.

One minute of in-game time is 90 frames. This could be lumped in with whatever needed 360 frames to only update every 4
minutes.

ALTHOUGH if one night is `6 hours = 6*60*90 = 32400 frames` then isn't the 130881600 thing pointless?

## Questions

[1]: https://youtu.be/ujg0Y5IziiY

[2]: https://www.reddit.com/r/fivenightsatfreddys/comments/2x6rw8/fnaf_1_decompiled_frame_by_frame/

[3]: https://www.reddit.com/r/technicalFNaF/comments/17zsw8e/comment/ka73aln/

[4]: https://youtu.be/shAkfUracYA
