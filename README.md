# LZW-Codec
It is a compression algorithm which creates a dictionary to add new combinations. Basically it compresses more if there are more repeating patterns.

Step1 : Read current and previous byte data.

Step2 : Concatinate precious and current data and check if it is in dictionary.

Step3 : If absent, add it to dictionary and output the code for current.
        Else, concatenate previous and current and continur step2.

Step4 : Change previous to current and continue till no data is available.
