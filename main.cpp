#include "ofp.h"

ofp::ofp()
{
	CtrlLayout(*this, "Window title");
}

GUI_APP_MAIN
{
	ofp().Run();
}
