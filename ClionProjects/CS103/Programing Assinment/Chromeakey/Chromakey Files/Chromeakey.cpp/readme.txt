CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name:Alex Valente

Email Address: valentea@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | ( 68,140 ,19  )  |  n/a
Arm                  | ( 255,160,115 )  | 210.2
Vest                 | ( 21,28  , 15 )  | 180
Shirt                | (  250,214,240)  | 250.9

================================== Review ===================================
1. Discuss and justify which pixels you chose to compute the average 
background value for method 1. Was there a reason not to choose more or
fewer pixels?

Response 1: The edges, because they are almost always green.

2. For method 1, do some experiments to find the range of distance thresholds 
for which the program seems to operate the best. You may use different 
thresholds for the two different sample images (Colbert and Bird). 
Note: threshold values that are too low will cause certain portions of the 
chroma key to stay in the picture; values that are too high will cause parts 
of the foreground image to disappear.

Response 2:

  Image                  Min Threshold           Max Threshold
  Colbert range:  from        60         to        70
  Bird range:     from     40            to       60


3. For method 2, explain what you implemented and why.  How did you go about 
implementing it? Walk us through a high-level description of what you did in 
your code (and use comments in the actual .cpp file to fill in the details). 
What other alternatives did you consider either before or after you
implemented your selected method?  What are the relative pros and cons of 
these methods? [This question is open-ended!]

Response 3: I did not get a chance to finish it, but it took the RGB value
and coverted to a Hexadsamal number. Then took a hex nember for all pixels
and made a (theretical) bell curve found average. Then took a standered 
devetion to the left and right and set those as the min and max values for
the chromakey (threshold). Then cast to the "mask" and so on and so forth.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:

Do you have any other remarks?

:
