#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMLTK.h"

class ofApp: public ofBaseApp{
	public:
  ofSoundStream soundStream;
  ofSoundStreamSettings soundStreamSettings;
  
  MLTK mltk;

  int numberOfOutputChannels = 0;
  int numberOfInputChannels = 2;
  int sampleRate = 44100;
  // Try different buffersizes to experiment with performance
  int bufferSize = 512;
  int frameSize = 2048;
  int hopSize = frameSize/2;
  int numberOfBuffers = 4;

  void setup();
  void update();
  void draw();

  map<string, float[2]> minMaxMap;

  void drawGraph(string algorithm, int x, int y, int w, int h);

  vector<string> algorithmList = {
    "BFCC.bands",
    "GFCC.bands",
    "MFCC.bands",
    "BFCC.coefs",
    "GFCC.coefs",
    "MFCC.coefs",
    "Spectrum",
    "SpectrumCQ",
    "Chromagram",
    "LPC.coefs",
    "LPC.reflection",
    "HPCP",
    "Windowing",
    "Phases",
    "Magnitudes",
    "FrameCutter",
    "LargeFrameCutter",
    "RMS",
  };

  bool showGui = true;
  ofxPanel gui;
  ofParameter<float> multiplier;

  void audioIn(ofSoundBuffer &inBuffer);
  
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
};
