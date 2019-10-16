#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
  // Setup the Window
  ofClear(ofColor::black);
  ofSetVerticalSync(true);
  ofSetWindowTitle("Listening Machines - Week 6 - Matrix Version");

  gui.setup("Press 'd' to toggle");
  gui.add(multiplier.set("Multiplier", 1.0, 0.1, 100.0));

  soundStream.setup(numberOfOutputChannels, numberOfInputChannels, sampleRate, bufferSize, numberOfBuffers);

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

void ofApp::drawGraph(string algorithm, int x, int y, int w, int h){
  // ConstantQ Spectrum
  if(algorithm == "RMS"){
    ofDrawBox(x, y, 0, w, h, w);
  } else {
    const vector<Real> &algo = mltk.getMeanData(algorithm);
    int n = MIN(algo.size(),w);
    const float algoWidth = (w / n);


    for(int i = 0; i < n; i++){
      float val = algo[i] * float(h);
      if(val < minMaxMap[algorithm][0]) minMaxMap[algorithm][0] = val;
      if(val > minMaxMap[algorithm][1]) minMaxMap[algorithm][1] = val;
      ofDrawRectangle(x + (i * algoWidth),
                      y,
                      algoWidth,
                      ofMap(val,
                            minMaxMap[algorithm][0],
                            minMaxMap[algorithm][1],
                            0.0,
                            -h));
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0,0,0);
  ofFill();
  ofSetColor(255);

//  const Real &rms = mltk.getValue("RMS");
//
//  // FrameCutter
//  const vector<Real> &frameCutter = mltk.getMeanData("FrameCutter");
//  const float frameWidth = (ofGetWidth()/frameCutter.size());
//
//  // Windowing
//  const vector<Real> &windowing = mltk.getData("Windowing");
//  const float windowWidth = (ofGetWidth()/windowing.size());
//
//  // Spectrum
//  const vector<Real> &spectrum = mltk.getMeanData("Spectrum");
//  const float spectrumWidth = (ofGetWidth()/spectrum.size());
//
//  // MFCC
//  const vector<Real> &mfccBands = mltk.getData("MFCC.bands");
//  const vector<Real> &mfccCoefs = mltk.getData("MFCC.coefs");
//  const float mfccBandWidth = (ofGetWidth()/mfccBands.size());
//  const float mfccCoefsWidth = (ofGetWidth()/mfccCoefs.size());
//
//  // BFCC
//  const vector<Real> &bfccBands = mltk.getData("BFCC.bands");
//  const vector<Real> &bfccCoefs = mltk.getData("BFCC.coefs");
//  const float bfccBandWidth = (ofGetWidth()/bfccBands.size());
//  const float bfccCoefsWidth = (ofGetWidth()/bfccCoefs.size());
//
//  // GFCC
//  const vector<Real> &gfccBands = mltk.getData("BFCC.bands");
//  const vector<Real> &gfccCoefs = mltk.getData("GFCC.coefs");
//  const float gfccCoefWidth = (ofGetWidth()/gfccCoefs.size());
//  const float gfccBandWidth = (ofGetWidth()/gfccBands.size());
//
//  // HPCP
//  const vector<Real> &hpcp = mltk.getData("HPCP");
//  const float hpcpWidth = (ofGetWidth()/hpcp.size());
//
//  const vector<Real> &chromagram = mltk.getData("Chromagram");
//  const float chromagramWidth = (ofGetWidth()/chromagram.size());
//
//  const vector<Real> &phases = mltk.getData("Phases");
//  const float phasesWidth = (ofGetWidth()/phases.size());
//
//  const vector<Real> &magnitudes = mltk.getData("Magnitudes");
//  const float magnitudesWidth = (ofGetWidth()/magnitudes.size());
//
//  const vector<Real> &lpcCoefs = mltk.getData("LPC.coefs");
//  const float lpcCoefsWidth = (ofGetWidth()/magnitudes.size());
//
//  const vector<Real> &lpcReflection = mltk.getData("LPC.reflection");
//  const float lpcReflectionWidth = (ofGetWidth()/lpcReflection.size());
//
//  string currentAlgorithm = "FrameCutter";

//  for(int i = 0; i < frameCutter.size(); i++){
//    float val = frameCutter[i] * ofGetHeight();
//    if(val < minMaxMap["FrameCutter"][0]) minMaxMap[currentAlgorithm][0] = val;
//    if(val > minMaxMap["FrameCutter"][1]) minMaxMap[currentAlgorithm][1] = val;
//    ofDrawRectangle(i * frameWidth,
//                    ofGetHeight(),
//                    frameWidth,
//                    ofMap(val,
//                          minMaxMap["FrameCutter"][0],
//                          minMaxMap["FrameCutter"][1],
//                          0.0,
//                          -ofGetHeight()));
//  }
  int counter = 0;
  for(int j = 0; j < 3; j++){
    for(int i = 0; i < 3; i++){
      drawGraph(algorithmList[counter], 10 + (i*ofGetWidth()/3), 330 + ((ofGetHeight()/3)*j), 270, 270);
      counter++;
    }
  }
  if(showGui){
    gui.draw();
  }
}

void ofApp::audioIn(ofSoundBuffer &inBuffer){
  if(numberOfInputChannels == 1) mltk.audioBuffer = inBuffer.getBuffer();
  if(numberOfInputChannels == 2){
    inBuffer.getChannel(mltk.leftAudioBuffer, 0);
    inBuffer.getChannel(mltk.rightAudioBuffer, 1);
  }
  if(numberOfInputChannels > 2){
    for(int j = 0; j < numberOfInputChannels; j++){
      cout << "More than 2 channels is not currently supported" << endl;
    }
  }
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
