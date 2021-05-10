#ifndef _ofp_ofp_h
#define _ofp_ofp_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <ofp/ofp.lay>
#include <CtrlCore/lay.h>

class ofp : public WithofpLayout<TopWindow> {
public:
	ofp();
};

#endif
