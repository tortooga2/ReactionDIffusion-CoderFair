#include "ofApp.h"


static int c = 1;
//--------------------------------------------------------------
void ofApp::setup(){
	//initialize
	render.allocate(W, H, GL_RGBA8);
	render.bindAsImage(4, GL_WRITE_ONLY);

	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "computershader.glsl");
	shader.linkProgram();

	if (shader.isLoaded()) {
		cout << "Compute shader loaded successfully." << endl;
	}
	else {
		cout << "Failed to load the compute shader." << endl;

	}

	int center_x = floor(W / 2);
	int center_y = floor(H / 2);

	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			int idx = x + y * W;
			A1cpu[idx] = 1.0;
			A2cpu[idx] = 1.0;
			if (rand() / float(RAND_MAX) < 0.0000001) {
				B1cpu[idx] = 1.0;
			}
			else {
				B1cpu[idx] = 0.0;
			}
			float distance = (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y);
			if ( distance < 1000 && distance > 900) {
				B1cpu[idx] = 1.0;
			}
			else {
				B1cpu[idx] = 0.0;
			}
			B1cpu[idx] = ofNoise(x/300.0, y/300.0);
			
			B2cpu[idx] = 0.0;
		}
	}
	
	//This allocates the Arrays into GPU memory
	A1.allocate(W * H * sizeof(float), A1cpu, GL_STATIC_DRAW);
	A2.allocate(W * H * sizeof(float), A2cpu, GL_STATIC_DRAW);
	B1.allocate(W * H * sizeof(float), B1cpu, GL_STATIC_DRAW);
	B2.allocate(W * H * sizeof(float), B2cpu, GL_STATIC_DRAW);
	//After allocating unlike the CPU the gpu does not know which is which. So we need to bind the buffer object or rather give it an ID. 
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0 /*ID*/);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
	B1.bindBase(GL_SHADER_STORAGE_BUFFER, 2);
	B2.bindBase(GL_SHADER_STORAGE_BUFFER, 3);


}

//--------------------------------------------------------------
void ofApp::update(){
	
	c = 1 - c;
	A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + c);
	A2.bindBase(GL_SHADER_STORAGE_BUFFER, 0 + 1-c);
	B1.bindBase(GL_SHADER_STORAGE_BUFFER, 2 + c);
	B2.bindBase(GL_SHADER_STORAGE_BUFFER, 2 + 1-c);


	shader.begin();
	shader.dispatchCompute(W / 20, H / 20, 1);
	shader.end();
	glGetError();
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	render.draw(0, 0);
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
