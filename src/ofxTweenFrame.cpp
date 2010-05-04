#include "ofxTweenFrame.h"

unsigned ofxTweenFrame::targetFrameRate;

void ofxTweenFrame::setParameters(int _id,  ofxEasing & _easing, ofxEasingType _type,  float _from, float _to, unsigned _duration, unsigned _delay){
	from.clear();
	to.clear();
	change.clear();
	pTarget.clear();

	id 		= _id;
	type 	= _type;
	easing 	= &_easing;
	if(easingFunction) delete easingFunction;
	switch(type){
	case easeIn:
		easingFunction = new ofxTweenDelegate(easing, &ofxEasing::easeIn);
	break;
	case easeOut:
		easingFunction = new ofxTweenDelegate(easing, &ofxEasing::easeOut);
	break;
	case easeInOut:
		easingFunction = new ofxTweenDelegate(easing, &ofxEasing::easeInOut);
	break;
	}

	addValue(_from,_to);

	// _duration is in milliseconds, convert it to seconds
	duration = int((_duration / 1000) * ofxTweenFrame::getTargetFrameRate());
	delay = int((_delay / 1000) * ofxTweenFrame::getTargetFrameRate());
	start();

	completed = false;
	running = true;

}

void ofxTweenFrame::start(){
	frameStart = ofGetFrameNum() + delay;
	frameStop = frameStart + duration;
}

void ofxTweenFrame::setDuration(uint _duration) {
	duration = (_duration * 1000) * ofxTweenFrame::getTargetFrameRate();
}

uint ofxTweenFrame::getDuration() {
	return duration;
}

float ofxTweenFrame::getTarget(unsigned pos) {
	if(pTarget.size()>pos)
		return pTarget[pos];
	else
		return 0;
}

float ofxTweenFrame::update() {
	if(!completed){

		int frameNum = ofGetFrameNum();

		if (frameNum == frameStop) {
			for(unsigned i=0; i<from.size(); i++){
				pTarget[i] = to[i];
			}
			running = false;
			completed = true;
			ofNotifyEvent(end_E,id);
		}

		else if(frameNum >= frameStart){
			ofxEasingArgs args;
			float elapsedTime = float(timestamp.elapsed());
			args.t= frameNum - frameStart;
			args.d= float(duration);
			for(unsigned i=0; i<from.size(); i++){
				args.b=from[i];
				args.c=change[i];

				easingFunction->notify(this,args);
				pTarget[i] = args.res;
			}
			running = true;
		}
	}
	return getTarget(0);
}
