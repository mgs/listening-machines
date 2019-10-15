#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
  // Setup the Window
  ofClear(ofColor::black);
  ofSetVerticalSync(true);
  ofSetWindowTitle("Listening Machines - Week 6");

  int numberOfOutputChannels = 0;
  int numberOfInputChannels = 2;
  int sampleRate = 44100;
  int frameSize = 2048;
  int hopSize = frameSize/2;
  int numberOfBuffers = 1;

  gui.setup("Press 'd' to toggle");
  gui.add(multiplier.set("Multiplier", 1.0, 0.1, 100.0));

  soundStream.setup(numberOfOutputChannels, numberOfInputChannels, sampleRate, frameSize, numberOfBuffers);

  // Setup MLTK using frameSize, sampleRate, and hopSize from above
  // The last parameter tells MLTK to use a default algorithm chain
  // that includes a larger number of algorithms. This is intended
  // for testing and for providing a reference chain that can then
  // be referred to while crafting your own chain in
  // `connectAlgorithmStream`
  mltk.setup(frameSize, sampleRate, hopSize, true);

  // Run MLTK one time to fill the pool with values
  mltk.run();

  // the minMaxMap provides a way of dynamically scaling
  // the values for different algorithms. This initializes
  // the minimums and maximums at their limits. These values
  // will get updated at runtime.
  for(auto s : algorithmList){
    // minimum
    minMaxMap[s][0] = 1000.0;
    // maximum
    minMaxMap[s][1] = -1000.0;
  }
}

//--------------------------------------------------------------
void ofApp::update(){
   mltk.run();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0,0,0);
  ofFill();
  ofSetColor(255);

  const Real &rms = mltk.getValue("RMS");

  // FrameCutter
  const vector<Real> &frameCutter = mltk.getData("FrameCutter");
  const float frameWidth = (ofGetWidth()/frameCutter.size());

  // Windowing
  const vector<Real> &windowing = mltk.getData("Windowing");
  const float windowWidth = (ofGetWidth()/windowing.size());

  // Spectrum
  const vector<Real> &spectrum = mltk.getMeanData("Spectrum");
  const float spectrumWidth = (ofGetWidth()/spectrum.size());

  // ConstantQ Spectrum
  const vector<Real> &spectrumcq = mltk.getMeanData("SpectrumCQ");
  const float spectrumcqWidth = (ofGetWidth()/spectrumcq.size());

  // MFCC
  const vector<Real> &mfccBands = mltk.getData("MFCC.bands");
  const vector<Real> &mfccCoefs = mltk.getData("MFCC.coefs");
  const float mfccBandWidth = (ofGetWidth()/mfccBands.size());
  const float mfccCoefsWidth = (ofGetWidth()/mfccCoefs.size());

  // BFCC
  const vector<Real> &bfccBands = mltk.getData("BFCC.bands");
  const vector<Real> &bfccCoefs = mltk.getData("BFCC.coefs");
  const float bfccBandWidth = (ofGetWidth()/bfccBands.size());
  const float bfccCoefsWidth = (ofGetWidth()/bfccCoefs.size());

  // GFCC
  const vector<Real> &gfccBands = mltk.getData("BFCC.bands");
  const vector<Real> &gfccCoefs = mltk.getData("GFCC.coefs");
  const float gfccCoefWidth = (ofGetWidth()/gfccCoefs.size());
  const float gfccBandWidth = (ofGetWidth()/gfccBands.size());

  // HPCP
  const vector<Real> &hpcp = mltk.getData("HPCP");
  const float hpcpWidth = (ofGetWidth()/hpcp.size());

  const vector<Real> &chromagram = mltk.getData("Chromagram");
  const float chromagramWidth = (ofGetWidth()/chromagram.size());

  const vector<Real> &phases = mltk.getData("Phases");
  const float phasesWidth = (ofGetWidth()/phases.size());

  const vector<Real> &magnitudes = mltk.getData("Magnitudes");
  const float magnitudesWidth = (ofGetWidth()/magnitudes.size());

  const vector<Real> &lpcCoefs = mltk.getData("LPC.coefs");
  const float lpcCoefsWidth = (ofGetWidth()/magnitudes.size());

  const vector<Real> &lpcReflection = mltk.getData("LPC.reflection");
  const float lpcReflectionWidth = (ofGetWidth()/lpcReflection.size());

  string currentAlgorithm = "SpectrumCQ";

  for(int i = 0; i < spectrumcq.size(); i++){
    float val = spectrumcq[i] * ofGetHeight();
    if(val < minMaxMap[currentAlgorithm][0]) minMaxMap[currentAlgorithm][0] = val;
    if(val > minMaxMap[currentAlgorithm][1]) minMaxMap[currentAlgorithm][1] = val;
    ofDrawRectangle(i * spectrumcqWidth,
                    ofGetHeight(),
                    spectrumcqWidth,
                    ofMap(val,
                          minMaxMap[currentAlgorithm][0],
                          minMaxMap[currentAlgorithm][1],
                          0.0,
                          -ofGetHeight()));
  }

  if(showGui){
    gui.draw();
  }
}

void ofApp::audioIn(ofSoundBuffer &inBuffer){
  inBuffer.getChannel(mltk.leftAudioBuffer, 0);
  inBuffer.getChannel(mltk.rightAudioBuffer, 1);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch(key){
    case 'd':
      showGui = !showGui;
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
