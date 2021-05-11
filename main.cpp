#include "ofp.h"

void decfile(String fn);

ofp::ofp()
{
	CtrlLayout(*this, "Window title");
	
	line.NullText(t_("Choose Oppo/Realme OFP file"));
	btn <<= THISBACK(onOpen);
}

void ofp::onOpen()
{
	fsel.Type("ofp files","*.ofp");
	if(fsel.ExecuteOpen(t_("open ofp file")))
	{
	
		String fn = fsel.Get();
		line.SetText(fn);
		
		decfile(fn);
	}
}

GUI_APP_MAIN
{
	ofp().Run();
}
