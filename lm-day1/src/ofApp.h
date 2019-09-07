#pragma once

// include statements
#include "ofMain.h"


class ofApp : public ofBaseApp{
	public:
    ofSoundStream soundStream;
    ofColor backgroundColor;
    ofMutex mutex;
    // On a mac you can check this in Audio MIDI Settings
  
    // This should match the number of input channels in your input
    int numberOfOutputChannels = 0;
    // This should match the number of input channels in your input
    int numberOfInputChannels = 2;
    // the sampleRate should match the rate of of your sound card, you can check
    // this "Audio MIDI Setup.app" found in the Utilities folder of Applications
    int sampleRate = 44100;
    // Try experimenting with different frameSize
    // You can try: 64, 128, 256, 512, 1024, 2048, 4096
    int frameSize = 1024;
    // Try some different values like: 1, 2, 4, 8. Do you notice anything?
    int numberOfBuffers = 4;
  
    // Audio Data
    //
    // For incoming audio data, we need to create a buffer to pair with each
    // variable. The buffer acts as a median between the audio thread and the
    // main thread thread that we use for our graphics.
    //
    // here we'll declare two vector<float> for the audioBuffers
    // the vector<float> keyword declares that we want a vector (essentially a
    // resizable array) and inside our vector will be float values.
    vector<float> audioBuffer;
    vector<float> audioThreadBuffer;

    // I'm adding another value here that will be useful to you guys, it's called
    // Root Mean Squared, or RMS. RMS provides an indication of the sound's
    // "brightness" and also tells us the total "energy" in a frame.
    float rms = 0.0;
    float rmsThreadBuffer = 0.0;

    // This is our audioIn(..) event that we added, it's a built-in mechanism
    // used by soundStream;
    void audioIn(ofSoundBuffer &inBuffer);

    // The rest of these are included by the project generator
  
    // These are the core functions
		void setup();
		void update();
		void draw();

    // These are the built-in event handlers
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
