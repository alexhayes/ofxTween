#ifndef TWEENFRAME_INCLUDED
#define TWEENFRAME_INCLUDED


#include "ofxTween.h"

class ofxTweenFrame : public ofxTween {

	public:
		void setParameters(int id, ofxEasing & easing, ofxEasingType type, float from, float to,  unsigned duration, unsigned delay);

		void start();

		float update();
		// calculates and applies a new value to the target

		float getTarget(unsigned pos);

		uint getDuration();
		void setDuration(uint duration);

		static unsigned targetFrameRate;
		static unsigned getTargetFrameRate() { return targetFrameRate; }

	protected:
		unsigned frameStart;
		unsigned frameStop;

};

#endif
