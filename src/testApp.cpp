#include "testApp.h"




// Color tracking test application. This code draws mostly from
// https://sites.google.com/site/ofauckland/examples/10-testing


//--------------------------------------------------------------
void testApp::setup(){
    
    w = 640;
    h = 480;
    
    targetHue = 20;
    tolerance = 2;
    
    grabber.setDeviceID(1);
    grabber.initGrabber(w, h, true);
    
    // Allocate
    rgb.allocate(w, h);
    hsv.allocate(w, h);
    hueImage.allocate(w, h);
    satImage.allocate(w, h);
    brightImage.allocate(w, h);
    hueFiltered.allocate(w, h);

}

//--------------------------------------------------------------
void testApp::update(){
    
    grabber.update();
    
    if (grabber.isFrameNew()){
        
    
        rgb.setFromPixels(grabber.getPixelsRef());
        
        rgb.mirror(false, true);
        
        hsv = rgb;
        
        hsv.convertRgbToHsv();
        
        hsv.convertToGrayscalePlanarImages(hueImage, satImage, brightImage);
        
        for (int i = 0; i < w * h; i++){
            
            int loopPix = hueImage.getPixels()[i];
            
            if (ofInRange(hueImage.getPixels()[i], targetHue - tolerance, targetHue + tolerance)){
                hueFiltered.getPixels()[i] = 255;
                
            } else {
                hueFiltered.getPixels()[i] = 0;
            }
            
        }
        
        hueFiltered.flagImageChanged();
        
        contourFinder.findContours(hueFiltered, 50, w*h/2, 1, false);
        
        
        
        
        
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    hsv.draw(0, 0);
    hueFiltered.draw(640, 0);
    rgb.draw(0,480);
    contourFinder.draw(0,0);
    contourFinder.draw(640,0);
    contourFinder.draw(0,480);
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    targetHue = hueImage.getPixels()[y * w + x];
    
    ofLogNotice() << targetHue;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
