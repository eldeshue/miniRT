# Summary on OneWeekendRaytracing to prepare to complete Minirt

##  Output an Image

- how to show an image?
  - The most straightful way is to write it to a file.
  - ←→ The pixels are written out in rows.
  - ➡️ Every row of pixels is written out left to right.
  - ⬇️ These rows ar written out from top to bottom
  - each of the color components are represnted internally by real-valued variavles.
    -  variables range from 0.0 to 1.0.
    - These must be scaled by Integer range before printing them out
  - RGB goes from fully off (black) to fully on (bright RGB)
    - Adding red and green light together make yellow so we can expect the bottom right corner to be yellow.