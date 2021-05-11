#include "ofp.h"

void decfile(String fn);

ofp::ofp()
{
	CtrlLayout(*this, t_("Window title"));
	
	line.NullText(t_("Choose Oppo/Realme OFP file"));
	e_prjname.NullText("projname");
	e_prjinfo.NullText("projinfo");
	e_cpu.NullText("cpu");
	e_flashtype.NullText("flash type");
	
	grid.AddColumn(t_("Name"));
	grid.AddColumn(t_("FileName"));
	grid.AddColumn(t_("Start"));
	grid.AddColumn(t_("Length"));
	grid.AddColumn(t_("Enc Length"));
	
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
