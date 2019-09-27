#include "ofApp.h"

  //--------------------------------------------------------------
void ofApp::setup(){
    // clear any leftovers from the memory
  ofClear(ofColor::black);
  
    // VerticalSync helps to prevent tearing but locks the framerate at the screen
    // refresh rate.
  ofSetVerticalSync(false);
  ofSetFrameRate(60);
  ofSetBackgroundAuto(false);
  ofSetWindowTitle("Listening Machine - Week2 - ");
  
    // setup the audio stream
  soundStream.setup(numberOfOutputChannels, numberOfInputChannels, sampleRate, frameSize, numberOfBuffers);
  
  
  mltk.setup(frameSize, sampleRate, frameSize/2);
  mltk.run();
  
  hpcpSmooth.assign(mltk.getData("HPCP").size(), 0);
    // Let's make ourselves some GUI
  const char* stats[4] = { "mean", "var", "min", "max" };
  
//  standard::Algorithm* aggr = standard::AlgorithmFactory::create("PoolAggregator",
//                                                                 "defaultStats", arrayToVector<string>(stats));
  
  prag.load("PragmataPro.ttf", 16);
  
  gui.setup("Press 'd' to toggle.");
  
  gui.add(showFps.set("Show Framerate In Title", true));
  gui.add(graphColor.set("Graph Color", ofColor(240,240,255)));
  gui.add(smoothingValue.set("Smoothing Value", 0.5, 0.0, 1.0));
  gui.add(coefsNoveltyFactor.set("MFCC Coefs Novelty Factor", 4.0, 0.0001, 8.0));
  gui.add(bandsNoveltyFactor.set("MFCC Bands Novelty Factor", 1.0, 0.0001, 1.0));
  
  
}

  //--------------------------------------------------------------
void ofApp::update(){
    // This will show us the framerate in the window's title bar
  if(showFps.get()){
    ofSetWindowTitle("Listening Machine - Week 2 - " + to_string(ofGetFrameRate()));
  }
    // this runs the analysis chain that's been declared inside ofxMLTK
  mltk.run();
}

  //--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  
  Real rms = mltk.getValue("RMS");
  vector<Real> mfcc_bands = mltk.getData("MFCC.bands");
  vector<Real> mfcc_coefs = mltk.getData("MFCC.coefs");
  vector<Real> spectrum = mltk.getData("Spectrum");
  
  vector<Real> hpcpUnsmooth = mltk.getData("HPCP");
  
  for(int i = 0; i < hpcpUnsmooth.size(); i++){
    hpcpSmooth[i] = ofInterpolateCosine(hpcpUnsmooth[i], hpcpSmooth[i], smoothingValue.get());
  }
  
  prag.drawString("hello", ofGetWidth()/2, ofGetHeight()/2);
    // We figure out the width of the buckets by just dividing the screen width
    // by the number of values in our frame
  float spectrumBucketWidth = (ofGetWidth() / float(spectrum.size()));
  float mfccBandWidth = (ofGetWidth() / float(mfcc_bands.size()));
  float mfccCoefsWidth = (ofGetWidth() / float(mfcc_coefs.size()));
  float hpcpWidth = (ofGetWidth() / float(hpcpUnsmooth.size()));
  
  ofSetColor(graphColor);
  
//  if(showBands){
//    for(int i = 0; i < mfcc_bands.size(); i++){
//      ofDrawRectangle(i * mfccBandWidth,
//                      ofGetHeight(),
//                      mfccBandWidth,
//                      -ofMap(mfcc_bands[i]/rms, 0, 1.0, 0, ofGetHeight(), true)*bandsNoveltyFactor.get());
//    }
//  }

  if(showBands){
    for(int i = 0; i < hpcpUnsmooth.size(); i++){
      ofDrawRectangle(i * hpcpWidth,
                      ofGetHeight(),
                      hpcpWidth,
                      -ofMap(hpcpSmooth[i], 0, 1.0, 0, ofGetHeight(), true)*bandsNoveltyFactor.get());
    }
  }
  
//  ofPolyline line;
//  
//  ofSetLineWidth(6);
//
//  for(int i = 0; i < hpcpSmooth.size(); i++){
//    line.lineTo(i * hpcpWidth,
//                ofGetHeight()/2 + -ofMap(hpcpSmooth[i], 0, 1.0, 0, ofGetHeight()/2, true)*bandsNoveltyFactor.get());
//  }
//  line.lineTo(ofGetWidth(), ofGetHeight()/2);

  
//  for(int i = 0; i < mfcc_coefs.size(); i++){
//    line.lineTo(i * mfccCoefsWidth,
//                ofGetHeight()/2 + ((mfcc_coefs[i])*coefsNoveltyFactor.get()));
//  }
//  line.lineTo(ofGetWidth(), ofGetHeight()/2);
//  if(showCoefs){
//    line.draw();
//  }
  
  if(showGui){
    gui.draw();
  }
   
  
//  ofSaveFrame();
}


  //-----
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
    case 'b':
      showBands = !showBands;
      break;
    case 'c':
      showCoefs = !showCoefs;
      break;
    case 'r':
      recording = !recording;
      break;
//    case 's':
//      standard::Algorithm* output = standard::AlgorithmFactory::create("YamlOutput",
//                                                                       "filename", "test.yaml");
//      output->input("pool").set(aggrPool);
//      output->compute();
//      break;
  }
}

  //--------------------------------------------------------------
void ofApp::keyReleased(int key){
  
}

  //--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
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
void ofApp::mouseEntered(int x, int y){
  
}

  //--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
  
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
