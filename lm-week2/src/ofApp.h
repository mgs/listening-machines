#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMLTK.h"

class ofApp : public ofBaseApp {
public:
  bool showGui = true;
  bool showBands = true;
  bool showCoefs = true;
  
  int numberOfOutputChannels = 0;
  int numberOfInputChannels = 2;
  int sampleRate = 44100;
  int frameSize = 1024;
  int numberOfBuffers = 4;
  
  ofColor backgroundColor;
  ofMutex mutex;
  MLTK mltk;

  ofxPanel gui;
  
  ofParameter<bool> showFps;
  ofParameter<ofColor> graphColor;
  ofParameter<float> coefsNoveltyFactor;
  ofParameter<float> bandsNoveltyFactor;

  ofSoundStream soundStream;
  
  void audioIn(ofSoundBuffer &inBuffer);
  
  // These are the built-ins
  void setup();
  void update();
  void draw();
  
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
