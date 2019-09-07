#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // This is just storing the background color in a variable
  backgroundColor = ofColor(0,0,0);
  // let's now use that variable to clear the sketch window so it doesn't flicker on startup
  ofClear(backgroundColor);
  // Vertical Sync locks the frame rate to the screen's refresh rate (usually 60FPS)
  // this helps avoid image tearing artifacts and is usually a good default
  ofSetVerticalSync(true);
  
  // This tells OF to automatically clear the background between frames turning it off is
  // useful in situations where you want to manually clear the screen
  ofSetBackgroundAuto(true);
  
  // This sets the title in the window's titlebar
  ofSetWindowTitle("Listening Machine 1");
  
  // setup the audio stream
  soundStream.setup(numberOfOutputChannels, numberOfInputChannels, sampleRate, frameSize, numberOfBuffers);
  
  // We initialize the vectors (resizable arrays) here.
  //
  // if we want to separately store left channel data
  // leftBuffer.assign(frameSize, 0.0);
  // leftThreadBuffer.assign(frameSize, 0.0);
  // if we want to separately store right channel data
  // rightBuffer.assign(frameSize, 0.0);
  // rightThreadBuffer.assign(frameSize, 0.0);

  // we create two buffers for storing our audio frames, one is for using from
  // our sketch while the other is for use inside the audioIn(..) event.
  audioBuffer.assign(frameSize, 0.0);
  audioThreadBuffer.assign(frameSize, 0.0);
}

//--------------------------------------------------------------
void ofApp::update(){
  // I forgot to mention this during class and some of you might have run into this
  // problem where the sketch crashes occasionally and gives some non-meaningful
  // error about illegal access. This is happening because the audioIn event is not
  // "thread-safe" which means memory collisions can happen behind the scenes. A very
  // efficient way of avoiding this is called a lock_guard. You can use it just like this:
  {
    std::lock_guard<std::mutex>mtx(mutex);
    audioBuffer = audioThreadBuffer;
    rms = rmsThreadBuffer;
  }
  // notice the { .. } that wraps this. That crreates a scope for the lock and
  // anonymizes the code block so it gets released when out of scope.
  //
  // Thank you to Roy Macdonald for demonstrating this.
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofClear(backgroundColor);
  
  ofFill();
  
  // We figure out the width of the buckets by just dividing the width by the number of values in our frame
  int bucketWidth = (ofGetWidth() / frameSize);
  
  for(int i = 0; i < frameSize; i++){
    // using the value of audio buffer we can start to meaningfully colorize the bars
    ofSetColor(255, ofMap(audioBuffer[i], -1.0, 1.0, 255, 0, true), ofMap(audioBuffer[i], -1.0, 1.0, 0, 255, true));
    
    ofDrawRectangle(i * bucketWidth, ofGetHeight()/2, bucketWidth, ofGetWidth()*audioBuffer[i]);
  }
}

//-----
void ofApp::audioIn(ofSoundBuffer &inBuffer){
  // Here we'll copy the incoming sound data into some buffer variables
  // first, let's grab the RMS of the current frame, this will give us the total
  // "energy" of the frame which will be useful for scaling and also is a decent
  // indicator of the "brightness" of a sound.
  rmsThreadBuffer = inBuffer.getRMSAmplitude();
  
  // Then we'll just iterate across the buffer using a for loop and we storing the
  // data into an intermediary variable that we use in update abovve. I updated this
  // so it should now work on 1 or 2 channel inputs.
  if(numberOfInputChannels == 1){
    for(int i = 0; i < inBuffer.getBuffer().size(); i += 2){
      audioThreadBuffer[i] = (inBuffer.getBuffer()[i]);
    }
  } else if(numberOfInputChannels == 2){
    for(int i = 0; i < inBuffer.getBuffer().size(); i += 2){
      audioThreadBuffer[i/2] = (inBuffer.getBuffer()[i] + inBuffer.getBuffer()[(i+1)])/2;
    }
  }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
