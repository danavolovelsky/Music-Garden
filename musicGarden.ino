#include <Adafruit_NeoPixel.h>
#include <arduinoFFT.h>

#define BUTTON 5
int currentMode = 0;


#define NEOPIXEL_PIN 6
#define NUM_PIXELS 37
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

#define SAMPLES 128 // determines into how many pieces signal should be broken down to
#define FREQ 44100 // in Hz
double REAL[SAMPLES]; //size of array set to SAMPLES amount; stores Amplitude
double IMAGINARY[SAMPLES];// phase of the signal at that frequency
double input[SAMPLES]; //stores input signal so it can be analysed 
double output[SAMPLES]; //stores FFT result

arduinoFFT FFT = arduinoFFT(REAL, IMAGINARY, SAMPLES, FREQ);//initializes instance of fft class

int soundPin = A0; // Defines analog pin for sound sensor
int threshold = 50; // Minimum volume level to trigger led

int circle1[] = {0};
int circle2[] = {1, 2, 3, 4};
int circle3[] = {5, 6, 7, 8, 9, 10, 11, 12};
int circle4[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
int circle5[] = {23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};

int bandValues[] = {0,0,0,0,0}; 
int BANDS_NUM = 4;

// Define colors for each circle
uint32_t color1 = pixels.Color(0,255,0); // red
uint32_t color2 = pixels.Color(49, 222, 99); // pink
uint32_t color3 = pixels.Color(0,148,211); // purple
uint32_t color4 = pixels.Color(0, 0, 139); // blue
uint32_t color5 = pixels.Color(64, 0, 0); // green

void fftFunction();

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pixels.begin();
}

void loop() {

  if (digitalRead(BUTTON) == LOW) {
  currentMode = (currentMode + 1) % 2; // Switch between mode 0 and 1
  delay(200); // Add a small delay to debounce the button
}

  brightnessFunction();
  fftFunction();

  pixels.show();
}

void brightnessFunction() {
  int soundValue = analogRead(soundPin); // Read the analog value from the sound sensor
  if (soundValue > threshold) { // Check if the sound value exceeds the threshold
    int brightness = map(soundValue, threshold, 1023, 0, 255); // Map the sound value to a brightness value

    pixels.setBrightness(brightness); // Set the brightness of the NeoPixel strip
  } else {
    pixels.clear(); // Clear the NeoPixel strip if the sound value is below the threshold
  }
}

void specialMode() {
  // Initialize bandValues array with zeros
  int bandValuesSpecial[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // Loop through the REAL array and get values in appropriate bands based on the frequency range
  for (int i = 1; i < (SAMPLES / 2); i++) {//https://github.com/s-marley/ESP32_FFT_VU/blob/master/FFT.xlsx
    if (REAL[i] > threshold) {
      if (i <= 0.5) {
        bandValues[1] += (int)REAL[i];
      } else if (i <= 1) {
        bandValues[2] += (int)REAL[i];
      } else if (i <= 2) {
        bandValues[3] += (int)REAL[i];
      } else if (i <= 3) {
        bandValues[4] += (int)REAL[i];
      } else if (i <= 4) {
        bandValues[5] += (int)REAL[i];
      } else if (i <= 5) {
        bandValues[6] += (int)REAL[i];
      } else if (i <= 6) {
        bandValues[7] += (int)REAL[i];
      } else if (i <= 8) {
        bandValues[8] += (int)REAL[i];
      } else if (i <= 11) {
        bandValues[9] += (int)REAL[i];
      } else if (i <= 15) {
        bandValues[10] += (int)REAL[i];
      } else if (i <= 19) {
        bandValues[11] += (int)REAL[i];
      } else if (i <= 26) {
        bandValues[12] += (int)REAL[i];
      } else if (i <= 34) {
        bandValues[13] += (int)REAL[i];
      } else if (i <= 45) {
        bandValues[14] += (int)REAL[i];
      } else if (i <= 65) {
        bandValues[15] += (int)REAL[i];
      } else if (i <= 90) {
        bandValues[16] += (int)REAL[i];
      } else if (i <= 130) {
        bandValues[17] += (int)REAL[i];
      } else if (i <= 180) {
        bandValues[18] += (int)REAL[i];
      }
    }
  }

  int colorChange = 256 / NUM_PIXELS;//amount by which the color values will change for each pixel
  int gradientSteps = NUM_PIXELS / 6; // Number of pixels within each gradient 

  for (int i = 0; i < NUM_PIXELS; i++) {  // Loop through each pixel and assign a color based position and band values

    int bandValueSpecial = bandValues[i];// Check corresponding band value for the current pixel

int red, green, blue;

if (i < gradientSteps) {  // first gradient range
  red = 255 - (i * colorChange * gradientSteps);// decreasing red
  green = i * colorChange * gradientSteps; //increasing green 
  blue = 0;

} else if (i < 2 * gradientSteps) { // second gradient range
  red = 255; // red max value
  green = 255 - ((i - gradientSteps) * colorChange * gradientSteps); //decreasing green 
  blue = 0;

} else if (i < 3 * gradientSteps) {//third gradient range
  red = 255 - ((i - 2 * gradientSteps) * colorChange * gradientSteps);//decreasing red
  green = 255; //green max value
  blue = 0;

} else if (i < 4 * gradientSteps) {//fourth gradient range 
  red = 0;
  green = 255;//max green value
  blue = (i - 3 * gradientSteps) * colorChange * gradientSteps;//increasing blue

} else if (i < 5 * gradientSteps) {//fifth gradient range
  red = 0;
  green = 255 - ((i - 4 * gradientSteps) * colorChange * gradientSteps);//decreasing green value
  blue = 255;//blue max value

} else {//sixth gradient range
  // Calculate the increasing red values and keep the blue value at maximum
  red = (i - 5 * gradientSteps) * colorChange * gradientSteps;//increasing red
  green = 0;
  blue = 255;//max blue value
}


if (bandValueSpecial > 0) {
  // If he pixel has sound in its frequency range, set color
  uint32_t pixelColor = pixels.Color(red, green, blue);
  pixels.setPixelColor(i, pixelColor);
} else {
  // No sound in the frequency range, turn off the pixel
  pixels.setPixelColor(i, 0);
}

  }}


void fftFunction(){

  for (int i = 0; i < SAMPLES; i++) {
    REAL[i] = analogRead(soundPin); // read input signal from microphone
  }

  FFT.Windowing(input, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//applies hamming filter to sound signal
  FFT.Compute(input, output, SAMPLES, FFT_FORWARD);// performs fft analysis on input signal and stores in output array
  FFT.ComplexToMagnitude(output, IMAGINARY, SAMPLES);// converts complex fft results to magnitude values that represents strength of each fequency component in sound signal

  for (int i = 1; i < (SAMPLES / 2); i++) {//loops through frequency components
    if (REAL[i] > threshold) {https://github.com/s-marley/ESP32_FFT_VU/blob/master/FFT.xlsx
      //Get the values in appropriate bands based on frequency range
      if (i <= 1)           bandValues[0]  += (int)REAL[i];//converts REAL (magnitude) value to bandvalue[0]
      if (i > 1 && i <= 2)  bandValues[1]  += (int)REAL[i];
      if (i > 2 && i <= 7)  bandValues[2]  += (int)REAL[i];
      if (i > 7 && i <= 25)  bandValues[3]  += (int)REAL[i];
      if (i > 25 && i <= 86)  bandValues[4]  += (int)REAL[i];
    }
  }

if (currentMode == 0) {
  for (int i = 0; i < sizeof(circle1) / sizeof(circle1[0]); i++) { //First bandvalue
    int pixelIndex = circle1[i];
    if (bandValues[0] > 0) {
      pixels.setPixelColor(pixelIndex, color1);//set color
    } else {
      pixels.setPixelColor(pixelIndex, 0); // Turn off the pixel
    }
  }

  for (int i = 0; i < sizeof(circle2) / sizeof(circle2[0]); i++) {//second bandvalue...
    int pixelIndex = circle2[i];
    if (bandValues[1] > 0) {
      pixels.setPixelColor(pixelIndex, color2);//set color
    } else {
      pixels.setPixelColor(pixelIndex, 0); // Turn off the pixel
    }
  }

  for (int i = 0; i < sizeof(circle3) / sizeof(circle3[0]); i++) {
    int pixelIndex = circle3[i];
    if (bandValues[2] > 0) {
      pixels.setPixelColor(pixelIndex, color3);//set color
    } else {
      pixels.setPixelColor(pixelIndex, 0); // Turn off the pixel
    }
  }

  for (int i = 0; i < sizeof(circle4) / sizeof(circle4[0]); i++) {
    int pixelIndex = circle4[i];
    if (bandValues[3] > 0) {
      pixels.setPixelColor(pixelIndex, color4);//set color
    } else {
      pixels.setPixelColor(pixelIndex, 0); // Turn off the pixel
    }
  }

  for (int i = 0; i < sizeof(circle5) / sizeof(circle5[0]); i++) {
    int pixelIndex = circle5[i];
    if (bandValues[4] > 0) {
      pixels.setPixelColor(pixelIndex, color5);
    } else {
      pixels.setPixelColor(pixelIndex, 0); // Turn off the pixel
    }
  }

} else if (currentMode == 1) {
    specialMode();
}
}


