# Music-Garden

# README - Music Visualizer with NeoPixel LEDs
This project is a music visualizer that uses NeoPixel LEDs to create a dynamic light display that reacts to the sound input. The visualizer performs Fast Fourier Transform (FFT) analysis on the sound signal and maps the frequency components to different color intensities on the individual NeoPixels.

# Research and Inspiration
My inspiration for this project is a combination of different sources. Firstly, I liked the concept of "Pulse Topology” by Rafael Lozano-Hemmer, where multiple light bulbs in a room respond to the heartbeats of the people present. This idea sparked my interest in visual displays of light. Secondly, I drew inspiration from light-up room speakers that change colors based on the music being played. These devices inspired me to incorporate music into my project.

To add a touch of serenity and a connection to nature, I envisioned a light-up flower garden—a sanctuary within the comfort of your own home. It combines the excitement of technology with the soothing presence of nature, providing a harmonious experience.

# Process
Initially, my plan was to use RGB LEDs for the music visualizer. However, I encountered a challenge with the Arduino Leonardo board, as it only has 6 PWM digital pins available. This limited number of pins wouldn't have been enough to drive the desired number of LEDs. So, I came up with an alternative solution: using regular LEDs in different colors and arranging them in an aesthetically pleasing pattern. Using regular LEDs had its own limitations, though. I couldn't use too many of them because of the limited PWM pins, and the options for creating visually appealing patterns were also quite limited. That's when I started considering using NeoPixels as a more feasible and convenient option. After some trial and error, it became clear that NeoPixels were the way to go. Initially, I had implemented a default mode with four circles representing different frequency ranges. However, upon further consideration, I wanted to enhance the visual experience and make it more interactive and fun. So, I decided to add another color and introduce a more colorful mode. This way, the music visualizer would provide a more engaging and enjoyable display. To perfect the code and test its functionality, I used a pixel LED strip. I kept refining the code until it worked exactly as I envisioned. However, when it came time to solder the individual pixels, I encountered unexpected difficulties and delays. Soldering the 40 pixels together in a continuous line proved to be a challenging task. Despite my efforts to secure the connections with solder and hot glue, they didn't hold up as well as I had anticipated, and the structure fell apart multiple times during the process. Considering future improvements, I would explore different methods of assembling the LED strip to avoid such complications. For example, instead of defining a single pixel LED pin, I might assign a separate pin for each circle. This could make the construction part less problematic and more robust. Additionally, as I added more LEDs to the setup, I had to introduce an external power source to support all the pixels adequately. This was necessary to ensure stable and consistent performance throughout the visualizer.

# Technical Overview
To start the music visualizer a sound sensor is used to capture the sound waves in the environment. The sound sensor converts these waves into an electrical signal, which represents the sound as a sequence of numbers. This analog signal is then sampled and stored in a collection for further analysis.

A mathematical algorithm called the Fast Fourier Transform (FFT) is applied to the sampled sound signal. This FFT algorithm breaks down the signal from its time-domain representation (how it changes over time) into a frequency-domain representation (the different frequencies it contains). By doing this, information about the amplitude (signal strength) and phase (position in the sample) of each frequency component is obtained.

The results of the FFT analysis are stored in arrays. Arrays to store the amplitude values (REAL) and phase values (IMAGINARY) for each frequency component. Additionally, the code includes arrays for the input and output signals used by the FFT algorithm to perform the analysis.

The music visualizer offers different modes to display the analyzed sound. In the default mode (mode 0), the code assigns specific frequency ranges to different sections of the LEDs. Each section is represented by a circle on the board and is given a particular color based on whether there is sound present within its assigned frequency range.

In the special mode (mode 1), the visualizer provides a more detailed representation. The LEDs are divided into multiple segments based on frequency ranges. Each pixel is assigned a color gradient that reflects the amplitude of the corresponding frequency components.

# Libraries used:
Adafruit_NeoPixel.h: This library provides functions to control NeoPixel LEDs. arduinoFFT.h: This library enables FFT analysis of the sound signal.

# Outcome
The outcome of running this code is a visually appealing music visualizer. The NeoPixels react to the input sound by displaying colors and patterns that correspond to the different frequency components present in the audio. The visualizer provides an interactive and dynamic representation of the sound, enhancing the overall audiovisual experience.

# References
To gather a better understanding of the Fast Fourier Transform as a concept and in code, I have looked at this YouTube video. For my code I specifically used the VU Meter FFT calculator Excel sheet and a version of the calculated generated code in it.

https://www.youtube.com/watch?v=Mgh2WblO5_c https://github.com/s-marley/ESP32_FFT_VU/blob/master/FFT.xlsx
