Cut down times ALOT with new method YAYAYAYAYAY

| PASSWORDS | TIMES: | crack.c      | VS | crack.py     |
|-----------|--------|--------------|----|--------------|
| YES       |        | 19 seconds   |    | <.1 second   |
| NO        |        | 11 seconds   |    | <.1 second   |
| TF        |        | 14 seconds   |    | <.1 second   |
| CA        |        | 3 seconds    |    | <.1 second   |
| nope      |        | 33.3 seconds |    | 35.7 seconds |
| ROFL      |        | 14.2 seconds |    | 16.4 seconds |


 These times show reinforce what I was attempting to do by tweaking my original crack.c
 I wanted to run the short PWs first, because it would be quicker to brute force simulate 1, 2 or 3 char PW compared to longer ones.
 This is reflected by the fact that my shorter PWs came out at lightning speed in crack.py while crack.c took much longer.
 However, it doesnt affect the speed of the PWs with the max amount of char (4 in this case), in fact it slows them down because we are giving priority to the shorter PWs thus, taking longer to get to the 4 char ones.
 This is a trade off worth having though, because the amount we tack onto the 4char PW ( ~ 2 seconds ) is marginal compared to how much time we save on shorter passwords( often 10+ seconds )

