# Tick-Data-Parser-and-Analyzer
Tick Data Parser and Analyzer
Goal: Learn to process large CSV tick datasets efficiently.

Key Concepts: File I/O, STL containers, basic statistics.

Pseudocode:
1.Define a structure to represent one tick with timestamp, price, and volume.
2.Open a CSV file containing tick data.
3.For each line in the file:
  a.Split the line into timestamp, price, and volume fields.
  b.Convert the text values into appropriate numeric types.
  c.Store the tick in a container (like a vector).
4.After loading all ticks:
  a.Compute basic statistics such as mean, variance, min, and max price.
  b.Display or save the summary to a new file.
5.Optionally, measure how long the file loading takes.
