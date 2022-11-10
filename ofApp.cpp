#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(0.5);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();

	float scale = 15;

	for (int i = 0; i < 3; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		for (int deg = 0; deg < 360; deg += 1) {

			auto location = glm::vec3(this->make_point(deg * DEG_TO_RAD) * scale, 0);
			location.x += ofMap(ofNoise(noise_seed.x, location.x * 0.045, ofGetFrameNum() * 0.0085), 0, 1, -30, 30);
			location.y += ofMap(ofNoise(noise_seed.y, location.y * 0.045, ofGetFrameNum() * 0.0085), 0, 1, -30, 30);

			this->frame.addVertex(location);
			this->frame.addColor(ofColor(255, 0, 0));
		}
	}

	for (int i = 0; i < this->frame.getNumVertices(); i++) {

		for (int k = i + 1; k < this->frame.getNumVertices(); k++) {

			auto distance = glm::distance(this->frame.getVertex(i), this->frame.getVertex(k));
			if (distance < 15) {

				this->frame.addIndex(i); this->frame.addIndex(k);
			}

			auto alpha = distance < 10 ? 255 : ofMap(distance, 10, 13, 255, 0);
			if (this->frame.getColor(i).a < alpha) {

				this->frame.setColor(i, ofColor(this->frame.getColor(i), alpha));
			}

			if (this->frame.getColor(k).a < alpha) {

				this->frame.setColor(k, ofColor(this->frame.getColor(k), alpha));
			}
		}

		
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->frame.drawVertices();

	for (int i = 0; i < this->frame.getNumVertices(); i++) {

		ofSetColor(this->frame.getColor(i));
		ofDrawSphere(this->frame.getVertex(i), ofMap(this->frame.getColor(i).a, 0, 255, 1, 0.1));
	}
}

//--------------------------------------------------------------
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}