#pragma once

#include "ofMain.h"

#define W 1920
#define H 1080

class ofApp : public ofBaseApp{

	public:
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
		
		ofBufferObject A1, A2, B1, B2;

		ofTexture render;
		ofShader shader;

		float A1cpu[W * H];
		float A2cpu[W * H];
		float B1cpu[W * H];
		float B2cpu[W * H];
};
