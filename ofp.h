#ifndef _ofp_ofp_h
#define _ofp_ofp_h

#include <CtrlLib/CtrlLib.h>
#include <GridCtrl/GridCtrl.h>
using namespace Upp;

#define LAYOUTFILE <ofp/ofp.lay>
#include <CtrlCore/lay.h>

class ofp : public WithofpLayout<TopWindow> {
public:
	typedef ofp CLASSNAME;
	ofp();
	
	StatusBar   status;
	FileSelNative fsel;
	
	void onOpen();
	void onExtract();
	
	void ShowStatus(String s);
	
	void decfile(String fn);
	void extracfile(String fn, String folder);

};

#endif
