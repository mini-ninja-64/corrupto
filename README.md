# corrupto
Command line corruptor written in C++

How to use:

executable infile outfile setting everyByte changeAmount

settings:

wobble0-7:
    Too many too explain, take a look at the wobble function

shift0-1:
    0:
      everyByte along swap with everyByte Index + changeAmount
    1:
      everyByte along swap with everyByte Index - changeAmount

adjust0-3:
    0:
      everyByte along + changeAmount (no - because you can just +-)
    1:
      everyByte along * changeAmount
    2:
      everyByte along / changeAmount
