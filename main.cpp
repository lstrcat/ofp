#include "ofp.h"

void brutekey(String encdata);

ofp::ofp()
{
	CtrlLayout(*this, "Window title");
}

GUI_APP_MAIN
{
	brutekey("");
	ofp().Run();
}
