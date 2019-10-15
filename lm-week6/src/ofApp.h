#pragma once

#include "ofMain.h"
#include "ofxMLTK.h"

class ofApp: public ofBaseApp{
	public:
  ofSoundStream soundStream;
  ofSoundStreamSettings soundStreamSettings;
  
  MLTK mltk;

  void setup();
  void update();
  void draw();

  map<string, float[2]> minMaxMap;
  vector<string> algorithmList = {
    "FrameCutter",
    "LargeFrameCutter",
    "Magnitudes",
    "Phases",
    "BFCC.coefs",
    "BFCC.bands",
    "GFCC.coefs",
    "GFCC.bands",
    "LPC.coefs",
    "LPC.reflection",
    "Chromagram",
    "Windowing",
    "Spectrum",
    "SpectrumCQ",
    "MFCC.coefs",
    "MFCC.bands",
    "HPCP",
    "RMS",
  };

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
