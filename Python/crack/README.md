Cut down times ALOT with new method YAYAYAYAYAY
PASSWORD    TIMES:  crack.py       VS        crack.c
  YES                 <1 s                      19 s
  NO                  <1 s                      11 s
  TF                  <1 s                      14 s
  CA                  <1 s                      3 s 
  nope                35 s                      33 s
  ROFL                16 s                      14 s


 These times show reinforce what I was attempting to do by tweaking my original crack.c
 I wanted to run the short PWs first, because it would be quicker to brute force simulate 1, 2 or 3 char PW compared to longer ones.
 This is reflected by the fact that my shorter PWs came out at lightning speed in crack.py while crack.c took much longer.
 However, it doesnt affect the speed of the PWs with the max amount of char (4 in this case), in fact it slows them down because we are giving priority to the shorter PWs thus, taking longer to get to the 4 char ones.
 This is a trade off worth having though, because the amount we tack onto the 4char PW ( ~ 2 seconds ) is marginal compared to how much time we save on shorter passwords( often 10+ seconds )

