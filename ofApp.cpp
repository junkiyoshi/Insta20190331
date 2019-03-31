#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofNoFill();

	this->frame_span = 30;
	this->size = 50;
	while (this->locations.size() < 100) {

		auto location = glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		bool flag = true;
		for (int i = 0; i < this->locations.size(); i++) {

			if (glm::distance(location, this->locations[i]) < this->size * 1.2) {

				flag = false;
				break;
			}
		}

		if (flag) {
		
			this->locations.push_back(location);
		}
	}

	for (int i = 0; i < 8; i++) {
	
		this->current_indexes.push_back(0);
		this->next_indexes.push_back(ofRandom(this->locations.size()));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % this->frame_span == 0) {
		
		for (int i = 0; i < this->current_indexes.size(); i++) {

			this->current_indexes[i] = this->next_indexes[i];

			vector<int> near_indexes;
			for (int location_index = 0; location_index < this->locations.size(); location_index++) {

				if (this->current_indexes[i] == location_index) { continue; }
				if (glm::distance(this->locations[this->current_indexes[i]], this->locations[location_index]) < this->size * 3) {

					near_indexes.push_back(location_index);
				}
			}

			if (near_indexes.size() > 0) {

				this->next_indexes[i] = near_indexes[ofRandom(near_indexes.size())];
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->current_indexes.size(); i++) {

		auto distance = glm::distance(this->locations[this->current_indexes[i]], this->locations[this->next_indexes[i]]);
		int frame_param = ofGetFrameNum() % this->frame_span;
		distance = ofMap(frame_param, 0, this->frame_span, 0, distance);
		ofDrawLine(this->locations[this->current_indexes[i]], this->locations[this->next_indexes[i]]);

		for (int location_index = 0; location_index < this->locations.size(); location_index++) {

			ofDrawCircle(this->locations[location_index], this->size * 0.45);

			if (this->current_indexes[i] == location_index) {

				ofFill();
				ofDrawCircle(this->locations[location_index], ofMap(frame_param, 0, this->frame_span, this->size * 0.45, 0));
				ofNoFill();
			}

			if (this->next_indexes[i] == location_index) {

				ofFill();
				ofDrawCircle(this->locations[location_index], ofMap(frame_param, 0, this->frame_span, 0, this->size * 0.45));
				ofNoFill();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}